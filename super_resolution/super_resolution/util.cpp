#include "util.h"
#include <immintrin.h>
#include "superResolution.h"
#define _ENABLE_AVX2 1

using namespace std;

void show(const int row, const int col, const float* mat) {
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cout << mat[r * col + c] << ", ";
		}
		cout << endl;
	}
}
void show_3d(const int channel, const int row, const int col, const float* mat) {
	for (int ch = 0; ch < channel; ch++) {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				cout << mat[ch * row * col + r * col + c] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
void show_CData(CDataBlob<float>& A) {
	for (int ch = 0; ch < A.channels; ch++) {
		cout << "ch: " << ch << endl;
		for (int r = 0; r < A.rows; r++) {
			for (int c = 0; c < A.cols; c++) {
				cout << A.ptr(r, c)[ch] << ", ";
			}
			cout << endl;
		}
	}
}


void convertA(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_w, float* A_pad) {
	//����C�����У�չ����A'�Ŀ�padding��A�Ŀ�
	for (int r = 0; r < rowC; r++) {
		for (int c = 0; c < colC; c++) {
			int wh = r * colC * convAw + c * convAw;

			int col1 = r * pad_w + c;
			A_convert[wh] = A_pad[col1];
			A_convert[wh + 1] = A_pad[col1 + 1];
			A_convert[wh + 2] = A_pad[col1 + 2];

			int col2 = (r + 1) * pad_w + c;
			A_convert[wh + 3] = A_pad[col2];
			A_convert[wh + 4] = A_pad[col2 + 1];
			A_convert[wh + 5] = A_pad[col2 + 2];

			int col3 = (r + 2) * pad_w + c;
			A_convert[wh + 6] = A_pad[col3];
			A_convert[wh + 7] = A_pad[col3 + 1];
			A_convert[wh + 8] = A_pad[col3 + 2];
		}
	}
}



void padding(const int pad_w, const int pad_h, const int colA, float* A_pad, const float* A) {
	for (int r = 0; r < pad_h; r++) {
		for (int c = 0; c < pad_w; c++) {
			int col = r * pad_w + c;//��ʵ����ƫ��������

			if (r == 0 || r == pad_h - 1) {
				A_pad[col] = 0;
			}
			else {
				if (c == 0 || c == pad_h - 1) {
					A_pad[col] = 0;
				}
				else {
					A_pad[col] = A[(r - 1) * colA + c - 1];
				}
			}
		}
	}
}

void padding_3d(const int pad_h, const int pad_w, const int rowA, const int colA, const int channel, float* A_pad, const float* A) {
	//һ��ͨ���ж��ٸ�ƫ������ ��A��˵��c*rowA*colA+r*colA+j
	//��A_pad��˵�� c*pad_w*pad_h+r*pad_w+j
	for (int ch = 0; ch < channel; ch++) {
		for (int r = 0; r < pad_h; r++) {

			if (r == 0 || r == pad_h - 1) {
				int col = ch * pad_w * pad_h + r * pad_w;
				memset(A_pad + col, 0, sizeof(float) * pad_w);
				continue;
			}

			for (int c = 0; c < pad_w; c++) {
				int col = ch * pad_w * pad_h + r * pad_w + c;//��ʵ����ƫ��������
				if (c == 0 || c == pad_w - 1) {
					A_pad[col] = 0;
				}
				else {
					A_pad[col] = A[ch * rowA * colA + (r - 1) * colA + c - 1];
				}
			}
		}
	}
	//���ַ����ܿ�2ms����[32,512,512]��

}


void Matrixmul_blas(const int convAh, const int convAw, float* A_convert, float* B, float* C) {
	const enum CBLAS_ORDER order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const int M = convAh;//A��������C������
	const int N = 1;//B��������C������
	const int K = convAw;//A��������B������
	const float alpha = 1;
	const float beta = 0;
	const int lda = K;
	const int ldb = N;
	const int ldc = N;

	cblas_sgemm(order, TransA, TransB, M, N, K, alpha, A_convert, lda, B, ldb, beta, C, ldc);



}

void Matrixmul3d_blas(const int convAh, const int convAw, const int channel, const int num_filters, float* A_convert, float* B_convert, float* C) {
	const enum CBLAS_ORDER order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasTrans;
	const int M = convAh;//A��������C������
	const int N = num_filters;//B��������C������
	const int K = convAw * channel;//A��������B������
	const float alpha = 1;
	const float beta = 0;
	const int lda = K;
	const int ldb = K;
	const int ldc = N;

	cblas_sgemm(order, TransA, TransB, M, N, K, alpha, A_convert, lda, B_convert, ldb, beta, C, ldc);



}

void convertA_3d(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, float* A_pad, const int channel)
{
	int pad_one_channel = pad_w * pad_h;
	int seg = channel * convAw;
	for (int c = 0; c < channel; c++)
	{
		for (int i = 0; i < rowC; i++)
		{
			for (int j = 0; j < colC; j++)
			{
				int wh = c * convAw + i * colC * seg + j * seg;

				int col1 = c * pad_one_channel + i * pad_w + j;
				A_convert[wh] = A_pad[col1];
				A_convert[wh + 1] = A_pad[col1 + 1];
				A_convert[wh + 2] = A_pad[col1 + 2];

				int col2 = c * pad_one_channel + (i + 1) * pad_w + j;
				A_convert[wh + 3] = A_pad[col2];
				A_convert[wh + 4] = A_pad[col2 + 1];
				A_convert[wh + 5] = A_pad[col2 + 2];

				int col3 = c * pad_one_channel + (i + 2) * pad_w + j;
				A_convert[wh + 6] = A_pad[col3];
				A_convert[wh + 7] = A_pad[col3 + 1];
				A_convert[wh + 8] = A_pad[col3 + 2];
			}
		}
	}
}

void convertA_3d_CD(CDataBlob<float>& A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, CDataBlob<float>& A_pad, const int channel)
{
	int pad_one_channel = pad_w * pad_h;
	int seg = channel * convAw;
	float* ptrA_C = A_convert.data;
	float* ptrA_p = A_pad.data;
	for (int c = 0; c < channel; c++)
	{
		for (int i = 0; i < rowC; i++)
		{
			for (int j = 0; j < colC; j++)
			{
				int wh = c * convAw + i * colC * seg + j * seg;

				int col1 = c * pad_one_channel + i * pad_w + j;
				ptrA_C[wh] = ptrA_p[col1];
				ptrA_C[wh + 1] = ptrA_p[col1 + 1];
				ptrA_C[wh + 2] = ptrA_p[col1 + 2];

				int col2 = c * pad_one_channel + (i + 1) * pad_w + j;
				ptrA_C[wh + 3] = ptrA_p[col2];
				ptrA_C[wh + 4] = ptrA_p[col2 + 1];
				ptrA_C[wh + 5] = ptrA_p[col2 + 2];

				int col3 = c * pad_one_channel + (i + 2) * pad_w + j;
				ptrA_C[wh + 6] = ptrA_p[col3];
				ptrA_C[wh + 7] = ptrA_p[col3 + 1];
				ptrA_C[wh + 8] = ptrA_p[col3 + 2];
			}
		}
	}
}


void convertA_SIMD(CDataBlob<float>& A_convert, const int rowC, const int colC, CDataBlob<float>& A_pad, const int channel) {
	//����A����opencv���������С�
	//ÿ�ζ�ȡĳλԪ�ص�����ͨ����һ��32ͨ�������������1���ϣ�һ����9��Ԫ�ء����һ����9*32��float��
	//��ָ��ֱ���������ڵ�3��ͷ��ַ��
	for (int row = 0; row < rowC; row++) {
		for (int col = 0; col < colC; col++) {
			float* pInput1 = A_pad.ptr(row, col);
			float* pInput2 = A_pad.ptr(row + 1, col);
			float* pInput3 = A_pad.ptr(row + 2, col);
		/*	int ph = 0;
			memcpy(A_convert.ptr(row*colC+col,0)+ph, pInput1, sizeof(float) * channel * 3);
			ph = ph + 3 * channel;
			memcpy(A_convert.ptr(row*colC +col, 0) + ph, pInput2, sizeof(float) * channel * 3);
			ph = ph + 3 * channel;
			memcpy(A_convert.ptr(row*colC+col, 0) + ph, pInput3, sizeof(float) * channel * 3);
			*/
			for (int ch = 0; ch < channel; ch += 8) {
				__m256 a, b, c;
				a = _mm256_load_ps(pInput1+ch);
				b = _mm256_load_ps(pInput2+ch);
				c = _mm256_load_ps(pInput3+ch);
				_mm256_store_ps(A_convert.ptr(row * colC + col, 0)+ch, a);
				_mm256_store_ps(A_convert.ptr(row * colC + col, 0)+3*channel+ch, b);
				_mm256_store_ps(A_convert.ptr(row * colC + col, 0)+6*channel+ch, c);

			}
		}
	}
	
}
void convertB_3d(float* B_convert, const int filters, const int channel, const int kernel, const float* B) {
	for (int r = 0; r < filters; r++) {
		int ptr = r * kernel * kernel * channel;
		memcpy(B_convert + ptr, B + ptr, sizeof(float) * ((size_t)kernel * kernel * channel));
	}
	//����ǵ�ת�á���
}

void convertC_3d(float* C_convert, const int convAh, const int num_filters, float* C) {
	for (int ch = 0; ch < num_filters; ch++) {
		for (int i = 0; i < convAh; i++) {
			C_convert[ch * convAh + i] = C[i * num_filters + ch];
		}
	}
}


void padding_forCDataBlob(CDataBlob<float>&A,CDataBlob<float>&A_pad,int rowA,int colA,int pad_h,int pad_w,int channel) {

	A_pad.setZero();
	//for (int r = 0; r < rowA; r++) {
	//	for (int c = 0; c < colA; c++) {
	//		for (int ch = 0; ch < channel; ch++) {
	//			A.ptr(r, c)[ch] = 1;
	//		}
	//	}
	//}
	//ʹ�������padding�����channel=32�������������channel<32�������Ǹ�����Ϊptrָ��Ķ��塣
	for (int r = 1; r < pad_h - 1; r++)
	{

		float* ptrA_pad = A_pad.ptr(r, 1);
		float* ptrA = A.ptr(r - 1, 0);
		memcpy(ptrA_pad, ptrA, sizeof(float) * channel * colA);

	}
	//��������������Ƚ���
	//for (int r = 1; r < pad_h - 1; r++)
	//{
	//	for (int c = 1; c < pad_w - 1; c++) {
	//		float* ptrA_pad = A_pad.ptr(r, c);
	//		float* ptrA = A.ptr(r - 1, c - 1);
	//		for (int ch = 0; ch < channel; ch++) {
	//			ptrA_pad[ch] = ptrA[ch];
	//		}
	//	}
	//}
}

void convertA_forCDataBlob(CDataBlob<float>& A_pad, CDataBlob<float>& convert_A,int rowC,int colC,int channel,int pad_h,int pad_w) {
	//convertA��rowC*colC�У�kernel*kernel*channel��,1ͨ��
	
	
	for (int r = 0; r < rowC; r++) {
		for (int c = 0; c < colC; c++) {
			float* ptr1 = A_pad.ptr(r, c);
			float* ptr2 = convert_A.ptr(0, 0)+ ((size_t)r * colC*9 + c*9)*channel;//(r*colC+c, 0);
			////cout << r << ", " << c << endl;
	/*		float* pInput1 = A_pad.ptr(r, c);
			float* pInput2 = A_pad.ptr(r + 1, c);
			float* pInput3 = A_pad.ptr(r + 2, c);

			for (int ch = 0; ch < channel*3; ch += 8) {
				__m256 a, b, ca;
				a = _mm256_load_ps(pInput1 + ch);
				b = _mm256_load_ps(pInput2 + ch);
				ca = _mm256_load_ps(pInput3 + ch);
				_mm256_store_ps(convert_A.ptr(r * colC + c, 0) + ch, a);
				_mm256_store_ps(convert_A.ptr(r * colC + c, 0) + 3 * channel + ch, b);
				_mm256_store_ps(convert_A.ptr(r * colC + c, 0) + 6 * channel + ch, ca);

			}*/
			//for (int i = 0; i < 3; i++) {
			//	float* ptr1 = A_pad.ptr(r, c+i);
			//	float* ptr2 = A_pad.ptr(r+1, c + i);
			//	float* ptr3 = A_pad.ptr(r + 2, c + i);
			//	for (int ch = 0; ch < channel; ch++) {
			//		convert_A.ptr(r * colC + c, ch+i*channel)[0] = ptr1[ch];
			//		convert_A.ptr(r * colC + c, ch + i * channel + 3*channel)[0] = ptr2[ch];
			//		convert_A.ptr(r * colC + c, ch + i * channel + 6*channel)[0] = ptr3[ch];
			//	}
			//}
			memcpy(ptr2, ptr1, sizeof(float) * 3 * channel);

			//for (int i = 0; i < 32*3; i++) {
			//	cout << ptr2[i] << ", " ;
			//	//cout << convert_A.ptr(0,0)[i] << ", ";
			//}
			//cout << endl;

			ptr1 = A_pad.ptr(r + 1, c);//A_padƫ����һ�У���0��.
			ptr2 = ptr2 + (size_t)3 * channel;
			memcpy(ptr2, ptr1, sizeof(float) * 3 * channel);



			ptr1 = A_pad.ptr(r + 2, c);
			ptr2 = ptr2 + (size_t)3 * channel;
			memcpy(ptr2, ptr1, sizeof(float) * 3 * channel);
		}
	}

	//���ھ�����ǰ���[num_filters,3*3,inchannel]���еģ�����ת��һ�¾ͺá�
}

void Matrixmul3d_blas_forCDataBlob( const int num_filters, const int convAw, const int convAh, const int channel, float*A_convert, float*kernel, float*C) {
	const enum CBLAS_ORDER order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasTrans;
	const int M = convAh;//A_convert.rows;//A��������C������
	const int N = num_filters;//B��������C������
	const int K = convAw * channel;//A_convert.cols;//A��������B������
	const float alpha = 1;
	const float beta = 0;
	const int lda = K;
	const int ldb = K;
	const int ldc = N;

	cblas_sgemm(order, TransA, TransB, M, N, K, alpha, A_convert, lda, kernel, ldb, beta, C, ldc);



}

void convertC_forCDatablob(CDataBlob<float>& C, CDataBlob<float>& C_convert) {
	//memcpy(C_convert.data, C.data, sizeof(float) * C.rows * C.cols);
	for (int r = 0; r < C_convert.rows; r++)
	{
		for (int c = 0; c < C_convert.cols; c++) {
			for (int ch = 0; ch < C_convert.channels; ch++) {
				C_convert.ptr(r, c)[ch] = C.data[r *C_convert.cols*C_convert.channels +c * C_convert.channels + ch];
			}
		}
	}
}