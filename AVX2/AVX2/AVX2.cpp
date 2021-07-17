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
	//�����ȳ˷�
	for (int i = 0; i < 32; i = i + 8) {
		a_float_x8 = _mm256_load_ps(a + i);
		b_float_x8 = _mm256_load_ps(b + i);

		sum_float_x8 = _mm256_add_ps(sum_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
		//������ڵİ�λ��ˣ�ÿ�β���8����ÿ���ۼ�����������8ָ����ÿ�ν���8��ͨ��������4�� 8ͨ���ۼ����������Ž���8ͨ��ˮƽ��ӣ���ɸ����صĵ�һ��ͨ����Ȼ���ڼ���һ��ƫ�


	}

	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);

	sum = ((float*)&sum_float_x8)[0] + ((float*)&sum_float_x8)[4];//
	cout << sum << endl;
	return sum;
}
/*
p1Ϊ����ͼ���ָ��
p2Ϊ�˲�����ָ��
p3Ϊ���ͼ���ָ��
numΪ�˲�������
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

inline bool vecAdd(const float * p1, float* p2, int num) {//p1ָ���˲���ƫ�p2ָ�����ͼ��ĳԪ�� ��ͨ��
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
	//ֱ�ӱ���
	for (int row = 0; row < outputData.rows; row++) {
		for (int col = 0; col < outputData.cols; col++) {
			float* pOut = outputData.ptr(row, col);
			const float* pIn = inputData.ptr(row, col);

			for (int ch = 0; ch < outputData.channels; ch++) {
				const float* pF = filters.weights.ptr(0, ch);//���ͼ��ĳԪ�صĵ�0��ͨ�������˲���ָ���0��Ԫ�أ���������ͨ��ȥ������ͼ���Ԫ�ص�����ͨ����ˣ��ۼӵõ������
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
		int srcy_start = row - 1;//ѡȡ�˲�����Ӧ������ͼ��ķ�Χ�� 
		int srcy_end = srcy_start + 3;//һ������
		srcy_start = MAX(0, srcy_start);//�п��ܻᳬ������ͼ�� ���ϱ�Ե
		srcy_end = MIN(srcy_end, inputData.rows);//�п��ܻᳬ�� ����ͼ����±�Ե

		for (int col = 0; col < outputData.cols; col++) {
			int srcx_start = col - 1;
			int srcx_end = srcx_start + 3;
			srcx_start = MAX(0, srcx_start);
			srcx_end = MIN(srcx_end, inputData.cols);

			float* pOut = outputData.ptr(row, col);//ָ�����ͼ���ĳ��ĳ��

			//����һ���˲�����3x3����������Ԫ��λ������ͼ��ĵ�0Ԫ�أ����е���һ�У����е���һ�С�
			for (int r = srcy_start; r < srcy_end; r++) {//r�Ļ��Χ��һ����������
				for (int c = srcx_start; c < srcx_end; c++) {
					//ѡȡ�˲�����Ӧ������ͼ��ķ�Χ��
					
					int filter_r = r - row + 1;//�˲�����ʼλ��Ϊ0��
					int filter_c = c - col + 1;//�˲�����ʼλ��Ϊ0��
					int filter_idx = filter_r * 3 + filter_c;//����

					//����ͼ���ͨ��Ĭ�����˲���������ͨ����ͬ�� ���ͼ���ͨ�����˲���������ͬ��
					vecMulAdd(inputData.ptr(r, c), filters.weights.ptr(0,filter_idx),pOut, filters.num_filters);//����ͼ���һ��Ԫ�����˲�����ӦԪ�ص�����ͨ����ˣ��ݴ档
					//�ڶ���Ԫ�����˲�����ӦԪ�ص�����ͨ����ˣ������һ�ε�������ӡ��Դ����ƣ�ֱ���˲�����Ӧ��9��Ԫ�ض��������ˣ���ô����ִ���˾���Ķ�Ӧλ�����ӣ��õ����ͼ��ĵ�ĳ��
					//��ĳ��Ԫ�ص�����ͨ����
				}
			}
			vecAdd();//�����ͼ��ĵ�ĳ�е�ĳ��Ԫ�ص�����ͨ�����϶�Ӧ��ƫ�

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