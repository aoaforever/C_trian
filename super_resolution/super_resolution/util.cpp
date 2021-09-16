#include "util.h"

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


void convertA(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_w, float* A_pad) {
	//传入C的行列，展开后A'的宽，padding后A的宽。
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
			int col = r * pad_w + c;//其实就是偏移量了啦

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
	//一个通道有多少个偏移量？ 对A来说，c*rowA*colA+r*colA+j
	//对A_pad来说， c*pad_w*pad_h+r*pad_w+j
	for (int ch = 0; ch < channel; ch++) {
		for (int r = 0; r < pad_h; r++) {

			if (r == 0 || r == pad_h - 1) {
				int col = ch * pad_w * pad_h + r * pad_w;
				memset(A_pad + col, 0, sizeof(float) * pad_w);
				continue;
			}

			for (int c = 0; c < pad_w; c++) {
				int col = ch * pad_w * pad_h + r * pad_w + c;//其实就是偏移量了啦
				if (c == 0 || c == pad_w - 1) {
					A_pad[col] = 0;
				}
				else {
					A_pad[col] = A[ch * rowA * colA + (r - 1) * colA + c - 1];
				}
			}
		}
	}
	//这种方法能快2ms，在[32,512,512]上

}

void Matrixmul_blas(const int convAh, const int convAw, float* A_convert, float* B, float* C) {
	const enum CBLAS_ORDER order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const int M = convAh;//A的行数，C的行数
	const int N = 1;//B的列数，C的列数
	const int K = convAw;//A的列数，B的行数
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
	const int M = convAh;//A的行数，C的行数
	const int N = num_filters;//B的列数，C的列数
	const int K = convAw * channel;//A的列数，B的行数
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
void convertB_3d(float* B_convert, const int filters, const int channel, const int kernel, const float* B) {
	for (int r = 0; r < filters; r++) {
		int ptr = r * kernel * kernel * channel;
		memcpy(B_convert + ptr, B + ptr, sizeof(float) * ((size_t)kernel * kernel * channel));
	}
	//过后记得转置。。
}

void convertC_3d(float* C_convert, const int convAh, const int num_filters, float* C) {
	for (int ch = 0; ch < num_filters; ch++) {
		for (int i = 0; i < convAh; i++) {
			C_convert[ch * convAh + i] = C[i * num_filters + ch];
		}
	}
}
