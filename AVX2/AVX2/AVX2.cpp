#include <iostream>	
#include <immintrin.h>
using namespace std;
void main()
{
	float a[32],b[32];
	for (int i = 0; i < 32; i++) {
		a[i] = 2;
		b[i] = 3;
	}
	cout << endl;
	
	float sum = 0.f;
	__m256 a_float_x8,b_float_x8;
	__m256 sum_float_x8 = _mm256_setzero_ps();
	//单精度乘法
	for (int i = 0; i < 32; i = i + 8) {
		a_float_x8 = _mm256_load_ps(a+i);
		b_float_x8 = _mm256_load_ps(b + i);

		sum_float_x8 = _mm256_add_ps(sum_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
		//卷积核内的按位相乘，每次操作8个，每次累加起来，步进8指的是每次进行8个通道，将这4个 8通道累加起来，最后才进行8通道水平相加，变成该像素的第一个通道，然后在加上一个偏差。


	}
	 
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);

	sum = ((float*)&sum_float_x8)[0] + ((float*)&sum_float_x8)[4];//
	cout << sum << endl;
	
	
	
}