#pragma once
#include <iostream>
#include<cblas.h>
#include "superResolution.h"
void show(const int row, const int col, const float* mat);
void show_3d(const int channel, const int row, const int col, const float* mat);
void show_CData(CDataBlob<float>& A);
void convertA(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_w, float* A_pad);
void padding(const int pad_w, const int pad_h, const int colA, float* A_pad, const float* A);
void padding_3d(const int pad_h, const int pad_w, const int rowA, const int colA, const int channel, float* A_pad, const float* A);
void Matrixmul_blas(const int convAh, const int convAw, float* A_convert, float* B, float* C);
void Matrixmul3d_blas(const int convAh, const int convAw, const int channel, const int num_filters, float* A_convert, float* B_convert, float* C);
void convertA_3d(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, float* A_pad, const int channel);
void convertA_3d_CD(CDataBlob<float>& A_convert, const int rowC, const int colC, const int convAw, const int pad_h, const int pad_w, CDataBlob<float>& A_pad, const int channel);
void convertA_SIMD(CDataBlob<float>& A_convert, const int rowC, const int colC, CDataBlob<float>& A_pad, const int channel);
void convertB_3d(float* B_convert, const int filters, const int channel, const int kernel, const float* B);
void convertC_3d(float* C_convert, const int convAh, const int num_filters, float* C);
void padding_forCDataBlob(CDataBlob<float>& A, CDataBlob<float>& A_pad, int rowA, int colA, int pad_h, int pad_w, int channel);
void convertA_forCDataBlob(CDataBlob<float>& A_pad, CDataBlob<float>& convert_A, int rowC, int colC, int channel, int pad_h, int pad_w);
void convertA_test_forCDataBlob(CDataBlob<float>& A, CDataBlob<float>& convert_A, int rowC, int colC, int channel);
//void convertA_forCDataBlob(CDataBlob<float>& A_pad, CDataBlob<float>& convert_A, int rowC, int colC, int channel);
void Matrixmul3d_blas_forCDataBlob(const int num_filters,const int convAh,const int convAw,const int channel, float* A_convert, float* kernel, float* C);
//void Matrixmul3d_blas_forCDataBlob(const int num_filters, CDataBlob<float>& A_convert, float* kernel, float* C);
//void Matrixmul3d_blas_forCDataBlob(const int num_filters, CDataBlob<float>& A_convert, Filters<float>& B, float* C);
//void convertA_forCDataBlob(CDataBlob<float>& A_pad, CDataBlob<float>& convert_A);
//void Matrixmul3d_blas_forCDataBlob(const int num_filters, CDataBlob<float>& A_convert, Filters<float>& B, CDataBlob<float>& C);

void convertC_forCDatablob(CDataBlob<float>& C, CDataBlob<float>& C_convert);

void convertC_addBias_forCDatablob(CDataBlob<float>& C, CDataBlob<float>& C_convert, Filters<float>& K);
