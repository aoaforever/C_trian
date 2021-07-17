#include <iostream>	
#include <immintrin.h>

#ifndef MAX
#define MAX(a,b) ((a)<(b)?(b):(a))
#endif // !MAX

#ifndef MIN
#define MIN(a,b) ((a)>(b)?(b):(a))
#endif // !MIN


using namespace std;


inline float dotproduct(const float *p1,const float* p2,int num) {

	float a[32], b[32];
	for (int i = 0; i < 32; i++) {
		a[i] = 2;
		b[i] = 3;
	}
	cout << endl;

	float sum = 0.f;

	__m256 a_float_x8, b_float_x8;
	__m256 sum_float_x8 = _mm256_setzero_ps();
	//单精度乘法
	for (int i = 0; i < 32; i = i + 8) {
		a_float_x8 = _mm256_load_ps(a + i);
		b_float_x8 = _mm256_load_ps(b + i);

		sum_float_x8 = _mm256_add_ps(sum_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
		//卷积核内的按位相乘，每次操作8个，每次累加起来，步进8指的是每次进行8个通道，将这4个 8通道累加起来，最后才进行8通道水平相加，变成该像素的第一个通道，然后在加上一个偏差。


	}

	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);

	sum = ((float*)&sum_float_x8)[0] + ((float*)&sum_float_x8)[4];//
	cout << sum << endl;
	return sum;
}
/*
p1为输入图像的指针
p2为滤波器的指针
p3为输出图像的指针
num为滤波器个数
*/
inline bool vecMulAdd(const float* p1, const float* p2, float* p3, int num) {
	__m256 a_float_x8, b_float_x8, c_float_x8;
	for (int i = 0; i < num; i += 8) {
		a_float_x8 = _mm256_load_ps(p1 + i);
		b_float_x8 = _mm256_load_ps(p2 + i);
		c_float_x8 = _mm256_load_ps(p3 + i);
		
		c_float_x8=_mm256_add_ps(c_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
		_mm256_storeu_ps(p3 + i, c_float_x8);
	}
}

inline bool vecAdd(const float * p1, float* p2, int num) {//p1指向滤波器偏差，p2指向输出图像某元素 的通道
	__m256 a_float_x8, b_float_x8;
	for (int i = 0; i < num; i += 8) {
		a_float_x8 = _mm256_load_ps(p1 + i);
		b_float_x8 = _mm256_load_ps(p2 + i);
		b_float_x8 = _mm256_add_ps(a_float_x8, b_float_x8);
		_mm256_store_ps(p2 + i, b_float_x8);
	}
}

template <class T>
class CDataBlob {
public:
	int rows;
	int cols;
	int channels;

	void setzero();
	T * ptr(int r, int c);
};

template <class T>
class Filters {
public:
	int num_filters;
	CDataBlob<T>  weights;

};
bool convolution(CDataBlob<float>& inputData, Filters<float>& filtersP, CDataBlob<float>& outputData,bool do_relu);


bool convolutionDP(CDataBlob<float>& inputData,
	Filters<float>& filtersP, Filters<float>& filtersD,
	CDataBlob<float>& outputData, bool do_relu)
{
	CDataBlob<float> tmp;
	bool r1 = convolution(inputData, filtersP, tmp, false);
	bool r2 = convolution(tmp, filtersD, outputData, do_relu);
	return r1 && r2;
}

bool convolution4layerUnit(CDataBlob<float>& inputData,
	Filters<float>& filtersP1, Filters<float>& filtersD1,
	Filters<float>& filtersP2, Filters<float>& filtersD2,
	CDataBlob<float>& outputData, bool do_relu)
{
	CDataBlob<float> tmp;
	bool r1 = convolutionDP(inputData, filtersP1, filtersD1, tmp, true);
	bool r2 = convolutionDP(tmp, filtersP2, filtersD2, outputData, do_relu);
	return r1 && r2;
}

bool convolution_1x1pointwise(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData) {
	//直接遍历
	for (int row = 0; row < outputData.rows; row++) {
		for (int col = 0; col < outputData.cols; col++) {
			float* pOut = outputData.ptr(row, col);
			const float* pIn = inputData.ptr(row, col);

			for (int ch = 0; ch < outputData.channels; ch++) {
				const float* pF = filters.weights.ptr(0, ch);//输出图像某元素的第0个通道，则滤波器指向第0个元素，用其所有通道去和输入图像该元素的所有通道相乘，累加得到结果。
				pOut[ch] = dotproduct(pIn, pF, inputData.channels);
				pOut[ch] += filters.biases.data[ch];
			}
		}
	}
	return true;
}
bool convolution_3x3depthwise(CDataBlob<float>&inputData, Filters<float>&filters, CDataBlob<float>&outputData) {
	//set all elements in outputData to zeros
	outputData.setzero();

	for (int row = 0; row < outputData.rows; row++) {
		int srcy_start = row - 1;//选取滤波器对应的输入图像的范围。 
		int srcy_end = srcy_start + 3;//一共三行
		srcy_start = MAX(0, srcy_start);//有可能会超过输入图像 的上边缘
		srcy_end = MIN(srcy_end, inputData.rows);//有可能会超过 输入图像的下边缘

		for (int col = 0; col < outputData.cols; col++) {
			int srcx_start = col - 1;
			int srcx_end = srcx_start + 3;
			srcx_start = MAX(0, srcx_start);
			srcx_end = MIN(srcx_end, inputData.cols);

			float* pOut = outputData.ptr(row, col);//指向输出图像的某行某列

			//定义一个滤波器，3x3，他的中心元素位于输入图像的第0元素，该行的上一行，该列的左一列。
			for (int r = srcy_start; r < srcy_end; r++) {//r的活动范围在一个滑动窗口
				for (int c = srcx_start; c < srcx_end; c++) {
					//选取滤波器对应的输入图像的范围。
					
					int filter_r = r - row + 1;//滤波器起始位置为0行
					int filter_c = c - col + 1;//滤波器起始位置为0列
					int filter_idx = filter_r * 3 + filter_c;//坐标

					//输入图像的通道默认于滤波器的输入通道相同？ 输出图像的通道与滤波器个数相同。
					vecMulAdd(inputData.ptr(r, c), filters.weights.ptr(0,filter_idx),pOut, filters.num_filters);//输入图像第一个元素与滤波器对应元素的所有通道相乘，暂存。
					//第二个元素与滤波器对应元素的所有通道相乘，再与第一次的数据相加。以此类推，直到滤波器对应的9个元素都操作过了，那么就是执行了卷积的对应位相乘相加，得到输出图像的第某行
					//第某列元素的所有通道。
				}
			}
			vecAdd();//将输出图像的第某行第某列元素的所有通道加上对应的偏差。

		}
	}
}



void main()
{
	float a[32], b[32],c[32];
	for (int i = 0; i < 32; i++) {
		a[i] = 2;
		b[i] = 3;
		c[i] = 0;
	}
	
}