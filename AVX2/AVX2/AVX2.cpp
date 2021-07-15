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
	//�����ȳ˷�
	for (int i = 0; i < 32; i = i + 8) {
		a_float_x8 = _mm256_load_ps(a+i);
		b_float_x8 = _mm256_load_ps(b + i);

		sum_float_x8 = _mm256_add_ps(sum_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
		//������ڵİ�λ��ˣ�ÿ�β���8����ÿ���ۼ�����������8ָ����ÿ�ν���8��ͨ��������4�� 8ͨ���ۼ����������Ž���8ͨ��ˮƽ��ӣ���ɸ����صĵ�һ��ͨ����Ȼ���ڼ���һ��ƫ�


	}
	 
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
	sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);

	sum = ((float*)&sum_float_x8)[0] + ((float*)&sum_float_x8)[4];//
	cout << sum << endl;
	
	
	
}