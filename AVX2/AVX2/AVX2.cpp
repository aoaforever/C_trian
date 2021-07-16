#include <iostream>	
#include <immintrin.h>
using namespace std;


float dotproduct() {

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

template <class T>
class CDataBlob {};

template <class T>
class Filters {};
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







void main()
{
	float a[32], b[32],c[32];
	for (int i = 0; i < 32; i++) {
		a[i] = 2;
		b[i] = 3;
		c[i] = 0;
	}
	
}