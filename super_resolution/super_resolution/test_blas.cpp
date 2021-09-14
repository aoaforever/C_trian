#include "superResolution.h"
#include <opencv2/opencv.hpp>
#include <cblas.h>
//		channels = 0;
//num_filters = 0;
//is_depthwise = false;
//is_pointwise = false;
//is_3x3 = false;
//with_relu = true;

#if 1
cv::TickMeter cvtm;
#define TIME_START cvtm.reset();cvtm.start();
#define TIME_END(FUNCNAME) cvtm.stop(); printf(FUNCNAME);printf("=%gms\n", cvtm.getTimeMilli());

#else
#define TIME_START
#define TIME_END(FUNCNAME)
#endif

void convertA(float* A_convert, const int rowC, const int colC, const int convAw, const int pad_w, float* A_pad) {
	//传入C的行列，展开后A'的宽，padding后A的宽。
	for (int r = 0; r < rowC; r++) {
		for (int c = 0; c < colC; c++) {
			int wh = r * colC * convAw + c * convAw;

			int col1 = r * pad_w + c;
			A_convert[wh] = A_pad[col1];
			A_convert[wh+1] = A_pad[col1+1];
			A_convert[wh+2] = A_pad[col1+2];

			int col2 = (r + 1) * pad_w + c;
			A_convert[wh + 3] = A_pad[col2];
			A_convert[wh + 4] = A_pad[col2+1];
			A_convert[wh + 5] = A_pad[col2+2];

			int col3 = (r + 2) * pad_w + c;
			A_convert[wh + 6] = A_pad[col3];
			A_convert[wh + 7] = A_pad[col3+1];
			A_convert[wh + 8] = A_pad[col3+2];
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

void padding_test() {
	//卷积参数初始化
	const int pad = 1;
	const int stride = 1;

	//定义A
	const int rowA = 5;
	const int colA = 5;
	const float A[rowA * colA] = {
		1,2,3,4,5,
		2,3,4,5,6,
		3,4,5,6,7,
		5,6,7,8,9,
		1,3,4,5,6
	};

	//定义卷积核
	const int rowK = 3;
	const int colK = rowK;
	float B[rowK * colK]{
		1,2,3,
		3,4,5,
		2,3,4
	};

	//计算C的宽高
	const int rowC = (rowA - rowK + 2 * pad) / stride + 1;
	const int colC = (colA - colK + 2 * pad) / stride + 1;
	//cout << rowC << endl << colC;
	//计算pad_A
	const int pad_w = rowA + 2 * pad;
	const int pad_h = colA + 2 * pad;
	float A_pad[pad_w * pad_h];
	padding(pad_w, pad_h, colA, A_pad, A);



	//for (int r = 0; r < pad_h; r++) {
	//	for (int c = 0; c < pad_w; c++) {
	//		cout << A_pad[r * pad_w + c] <<", ";
	//	}
	//	cout << endl;
	//}

	//定义A'的宽高
	const int convAw = rowK * rowK;
	const int convAh = rowC *colC ;

	float A_convert[convAh * convAw];
	convertA(A_convert, rowC, colC, convAw, pad_w, A_pad);

	for (int r = 0; r < convAh; r++) {
		for (int c = 0; c < convAw; c++) {
			cout << A_convert[r * convAw + c] << ", ";
		}
		cout << endl;
	}

}
void cblascolmajor() {
	const int rowK = 3;
	const int colK = 3;
	const int channelK = 3;
	const int num_filters = 3;

	//卷积核K
		const float kernel[num_filters * rowK * colK * channelK] = {
			1,0,1,
			0,1,0,
			1,1,1,

			2,0,1,
			0,1,0,
			1,1,1,

			3,0,1,
			0,1,0,
			1,1,1,

			100,0,1,
			0,1,0,
			1,1,1,

			200,0,1,
			0,1,0,
			1,1,1,

			300,0,1,
			0,1,0,
			1,1,1,

			4,0,1,
			0,1,0,
			1,1,1,

			5,0,1,
			0,1,0,
			1,1,1,

			6,0,1,
			0,1,0,
			1,1,1,

	};

	for (int r = 0; r < 3 * 3 * 3; r++) {
		for (int c = 0; c < 3; c++) {
			cout << kernel[r + c * 27] << ", ";
		}
		cout << endl;
	}

	/*  1, 100, 4,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		2, 200, 5,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		3, 300, 6,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		*/
}


void img2col() {
	const int rowA = 5;
	const int colA = 5;
	const int channelA = 1;

	const int rowK = 3;
	const int colK = 3;
	const int channelK = 1;
	const int num_filters = 1;
	//被卷积矩阵A
	const float A[rowA * colA * channelA] = { 1,2,3,4,5,
											  6,7,8,9,0,
											  2,3,4,5,6,
											  7,8,9,0,1,
											  3,4,5,6,7};

	//卷积核K
	const float kernel[num_filters*rowK * colK * channelK] = { 
		1,0,1,
		0,1,0,
	    1,1,1,
	};



	//计算卷积输出矩阵的宽和高。
	const int rowOut = rowA-rowK+1;
	const int colOut = colA-colK+1;
	const int channelOut = num_filters;

	//Hout=  ((Hin + 2*padding[0]- dilation[0]* (kernel_size[0]-1) -1 )  / stride)  +1
	//Wout=  ((Win + 2*padding[1]- dilation[1]* (kernel_size[1]-1) -1 )  / stride)  +1
	 
	//计算被卷积矩阵的宽和高，展开后的矩阵高宽
	const int colConv = rowK * colK * channelK;//宽,K x K x Cin
	const int rowConv = rowOut*colOut;//////注意这里，高
	

	//转换被卷积矩阵A，求展开后的矩阵
	float A_convert[rowConv * colConv ] = { 0 };
	//将9个数据放到A_convert的一行
	for (int r = 0; r < rowOut; r++) {
		for (int c = 0; c < colOut; c++) {
			int wh = r * colOut * colConv + c * colConv;//A_convert偏移量
			int col1 = r * rowA + c;//滑动窗口偏移量
			A_convert[wh] = A[col1];
			A_convert[wh+1] = A[col1+1];
			A_convert[wh+2] = A[col1+2];

			int col2 = (r +1)* rowA + c;
			A_convert[wh+3] = A[col2];
			A_convert[wh + 4] = A[col2 + 1];
			A_convert[wh + 5] = A[col2 + 2];

			int col3 = (r+2) * rowA + c;
			A_convert[wh+6] = A[col3];
			A_convert[wh + 7] = A[col3 + 1];
			A_convert[wh + 8] = A[col3 + 2];

		}
	}


	const enum CBLAS_ORDER Order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const int M = rowConv;//A的行，C的行
	const int N = 1;//B的列，C的列，filters的个数
	const int K = colConv;//A的列，B的行
	const float alpha = 1;
	const float beta = 0;
	const int lda = K;
	const int ldb = N;
	const int ldc = N;


	//定义卷积输出矩阵
	float C[M * N];
	cblas_sgemm(Order, TransA, TransB, M, N, K, alpha, A_convert, lda, kernel, ldb, beta, C, ldc);

	for (int r = 0; r < rowOut; r++) {
		for (int c = 0; c < colOut; c++) {
			cout << C[r * colOut + c] << ", ";
		}
		cout << endl;
	}


}



void main() {
	padding_test();
	//img2col();
	//CDataBlob<float> input,C;

	//ConvInfoStruct kernel1{ 32,32,false,false,true,false };
	//Filters<float> kernel;
	//kernel = kernel1;
	//input.create(512, 512, 32*9);
	//cout << "OK" << endl;
	//C.create(32, 512*512, 1);
	//cout << "OK1" << endl;
	//int r = 32;
	//int c = 512*512;
	//int k = 32*9;
	//TIME_START
	//cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasConjNoTrans, r, c, k, 1, kernel.weights.data, 32*9, input.data, 512*512, 0, C.data, 512*512);
	//TIME_END("openBlas")

	//CDataBlob<float> input1, output;
	//input1.create(512, 512, 32);
	////output.create(512, 512, 32);
	//TIME_START
	//convolution(input1, kernel, output, false);
	//TIME_END("CONV")

}