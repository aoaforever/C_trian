#pragma once
#include <iostream>
#include<cblas.h>
void show(const int row, const int col, const float* mat);
void show_3d(const int channel, const int row, const int col, const float* mat);
void convertA(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_w, float* A_pad);
void padding(const int pad_w, const int pad_h, const int colA, float* A_pad, const float* A);
void padding_3d(const int pad_h, const int pad_w, const int rowA, const int colA, const int channel, float* A_pad, const float* A);
void Matrixmul_blas(const int convAh, const int convAw, float* A_convert, float* B, float* C);
void Matrixmul3d_blas(const int convAh, const int convAw, const int channel, const int num_filters, float* A_convert, float* B_convert, float* C);
void convertA_3d(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, float* A_pad, const int channel);
void convertB_3d(float* B_convert, const int filters, const int channel, const int kernel, const float* B);
void convertC_3d(float* C_convert, const int convAh, const int num_filters, float* C);
//
////void padding_3d22(const int pad_h, const int pad_w, const int rowA, const int colA, const int channel, float* A_pad, const float* A) {
//	//一个通道有多少个偏移量？ 对A来说，c*rowA*colA+r*colA+j
//	//对A_pad来说， c*pad_w*pad_h+r*pad_w+j
//	for (int ch = 0; ch < channel; ch++) {
//		for (int r = 0; r < pad_h; r++) {
//
//			if (r == 0 || r == pad_h - 1) {
//				int col = ch * pad_w * pad_h + r * pad_w;
//				memset(A_pad + col, 0, sizeof(float) * pad_w);
//				continue;
//			}
//
//			for (int c = 0; c < pad_w; c++) {
//				int col = ch * pad_w * pad_h + r * pad_w + c;//其实就是偏移量了啦
//				if (c == 0 || c == pad_w - 1) {
//					A_pad[col] = 0;
//				}
//				else {
//					A_pad[col] = A[ch * rowA * colA + (r - 1) * colA + c - 1];
//				}
//			}
//		}
//	}
//}


void convertA_322d(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, float* A_pad, const int channel)
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
