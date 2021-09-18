#include "superResolution.h"
#include <opencv2/opencv.hpp>

#include"util.h"

#if 1
cv::TickMeter cvtm;
#define TIME_START cvtm.reset();cvtm.start();
#define TIME_END(FUNCNAME) cvtm.stop(); printf(FUNCNAME);printf("=%gms\n", cvtm.getTimeMilli());

#else
#define TIME_START
#define TIME_END(FUNCNAME)
#endif
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


	show(pad_h, pad_w, A_pad);


	//定义A'的宽高
	const int convAw = rowK * rowK;
	const int convAh = rowC *colC ;

	float A_convert[convAh * convAw];
	convertA(A_convert, rowC, colC, convAw, pad_w, A_pad);
	show(convAh, convAw, A_convert);




	//定义C
	float C[convAh * 1];
	Matrixmul_blas(convAh, convAw, A_convert, B, C);
	cout << "C is:" << endl;
	show(rowC, colC, C);

}

void padding_3d_test() {
	const int pad = 1;
	const int stride = 1;

	//定义A三维
	const int rowA = 3;
	const int colA = 4;
	const int channel = 4;
	const float A[channel * rowA * colA] = {
		1,2,3,4,
		2,3,4,5,
		3,4,5,6,
	

		100,2,3,4,
		2,3,4,5,
		3,4,5,6,
	

		200,2,3,4,
		2,3,4,5,
		3,4,5,6,

		300,2,3,4,
		2,3,4,5,
		3,4,5,6
	
	};
	//show_3d(channel, rowA, colA, A);
	//定义三维卷积核
	const int num_filters = 2;
	const int kernel = 3;
	float B[num_filters*kernel * kernel * channel] = {
		1,1,1,
		1,1,1,
		2,2,2,

		3,3,3,
		3,2,3,
		4,3,5,

		2,3,4,
		3,4,5,
		2,3,4,

		40,3,4,
		3,4,5,
		2,3,4,

		100,1,1,
		1,1,1,
		2,2,2,

		3,3,3,
		3,2,3,
		4,3,5,

		2,3,4,
		3,4,5,
		2,3,4,

		221,3,4,
		3,4,5,
		2,3,4
	};

	
	//计算C的高宽
	const int rowC = (rowA - kernel + 2 * pad) / stride + 1;
	const int colC = (colA - kernel + 2 * pad) / stride + 1;
	const int outchannel = num_filters;
	
	//计算三维pad_A
	const int pad_w = colA + 2 * pad;
	const int pad_h = rowA + 2 * pad;
	float A_pad[channel * pad_w * pad_h];
	padding_3d(pad_h, pad_w, rowA, colA, channel, A_pad, A);
	show_3d(channel, pad_h, pad_w, A_pad);

	//计算A'
	const int convAw = kernel * kernel;//注意这里没channel
	const int convAh = rowC * colC;
	float A_convert[convAw * convAh*channel];//注意这里的channel
	convertA_3d(A_convert, rowC,colC, convAw, pad_h,pad_w, A_pad, channel);
	show(convAh, convAw * channel, A_convert);
	
	const int rowK = num_filters;
	const int colK = kernel * kernel * channel;
	float B_convert[rowK * colK];
	TIME_START
	convertB_3d(B_convert, num_filters, channel, kernel, B);
	TIME_END("convertB")
	show(rowK, colK, B_convert);

	//记得转置卷积核的展开B_convert
	float C[convAh*num_filters];
	TIME_START
	Matrixmul3d_blas(convAh, convAw, channel, num_filters, A_convert, B_convert, C);
	TIME_END("blas")
	float C_convert[rowC * colC * num_filters];
	TIME_START
	convertC_3d(C_convert, convAh, num_filters, C);
	TIME_END("convertC")
	show_3d(num_filters, rowC, colC, C_convert);
}
void padding_32d_test() {
	const int pad = 1;
	const int stride = 1;

	//定义A三维
	const int rowA = 512;
	const int colA = 512;
	const int channel = 32;
	float* A = (float*)malloc(sizeof(float) * rowA * colA * channel);

	//show_3d(channel, rowA, colA, A);
	//定义三维卷积核
	const int num_filters = 32;
	const int kernel = 3;
	float* B = (float*)malloc(sizeof(float) * kernel * kernel * channel * num_filters);


	//计算C的高宽
	const int rowC = (rowA - kernel + 2 * pad) / stride + 1;
	const int colC = (colA - kernel + 2 * pad) / stride + 1;
	const int outchannel = num_filters;

	//计算三维pad_A
	const int pad_w = colA + 2 * pad;
	const int pad_h = rowA + 2 * pad;
	float *A_pad=(float*)malloc(sizeof(float)*pad_w*pad_h*channel);
	//TIME_START
	padding_3d(pad_h, pad_w, rowA, colA, channel, A_pad, A);
	//TIME_END("padding")
	free(A);
	//show_3d(channel, pad_h, pad_w, A_pad);

	//计算A'
	const int convAw = kernel * kernel;//注意这里没channel
	const int convAh = rowC * colC;
	float *A_convert=(float*)malloc(sizeof(float)*convAw * convAh * channel);//注意这里的channel
	//TIME_START
	convertA_3d(A_convert, rowC, colC, convAw, pad_h, pad_w, A_pad, channel);
	//TIME_END("convertA")
	free(A_pad);
	//show(convAh, convAw * channel, A_convert);

	const int rowK = num_filters;
	const int colK = kernel * kernel * channel;
	float *B_convert=(float*)malloc(sizeof(float)*rowK*colK);
	//TIME_START
	convertB_3d(B_convert, num_filters, channel, kernel, B);
	//TIME_END("convertB")
	free(B);
	//show(rowK, colK, B_convert);

	//记得转置卷积核的展开B_convert
	float *C=(float*)malloc(sizeof(float)*convAh * num_filters);
	//TIME_START
	Matrixmul3d_blas(convAh, convAw, channel, num_filters, A_convert, B_convert, C);
	//TIME_END("blas")
	float *C_convert=(float*)malloc(sizeof(float)* rowC * colC * num_filters);
	//TIME_START
	convertC_3d(C_convert, convAh, num_filters, C);
	//TIME_END("convertC")
	free(C);
	//show_3d(num_filters, rowC, colC, C_convert);

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

void convertA_simd_test() {
	CDataBlob<float> A_pad,A_Convert;
	const int rowC = 512;
	const int colC = 512;
	const int channel = 32;
	int convAw = 9;
	int pad_h = 514;
	int pad_w = 514;
	A_pad.create(514, 514, 32);
	A_Convert.create(512 * 512, 9 * channel,1);
	
	//convertA_SIMD(A_Convert, rowC, colC, A_pad, channel);
	convertA_3d_CD(A_Convert, rowC, colC, convAw, pad_h, pad_w, A_pad, channel);
}
//
//void blas_Cdatablob_Test(int rowA,int colA,int channel) {
//
//
//
//	CDataBlob<float> A, A_pad;
//	
//	
//	int pad_w = colA + 2;
//	int pad_h = rowA + 2;
//
//	int colC = colA;
//	int rowC = rowA;
//	A.create(rowA, colA, channel);
//	A_pad.create(pad_h, pad_w, channel);
//
//	TIME_START
//		padding_forCDataBlob(A, A_pad, rowA, colA, pad_h, pad_w, channel);
//	//cout << A_pad << endl;
//	//TIME_END("padding")
//
//	CDataBlob<float> convert_A;
//	convert_A.create(rowC * colC, 3 * 3 * channel, 1);
//	//TIME_START
//	convertA_forCDataBlob(A_pad, convert_A);
//	//TIME_END("convertA");
//
//	int num_filters = 32;
//	CDataBlob<float>C;
//	C.create(rowC * colC, num_filters, 1);
//	Filters<float> kernel(32, 32, false, false, true, false);
//	kernel.weights.create(num_filters, 9, 32);
//	//TIME_START
//	Matrixmul3d_blas_forCDataBlob(num_filters, convert_A, kernel, C);
//	//TIME_END("blas");
//
//	CDataBlob<float>C_convert;
//	C_convert.create(rowC, colC, num_filters);
//	//TIME_START
//	convertC_forCDatablob(C, C_convert);
//	TIME_END("total")
//
//}

void blas_Cdatablob_Test_forsure(int rowA, int colA, int channel) {

	float a[32*9] = { 
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,


	};
	float k[32*9] = { 
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, };

	CDataBlob<float> A, A_pad;


	int pad_w = colA + 2;
	int pad_h = rowA + 2;

	int colC = colA;
	int rowC = rowA;
	A.create(rowA, colA, channel);

	A_pad.create(pad_h, pad_w, channel);
	
	for (int ch = 0; ch < channel; ch++) {
		for (int r = 0; r < rowA; r++) {
			for (int c = 0; c < colA; c++) {
				A.ptr(r, c)[ch] = a[r * 3 + c];
			}
		}
	}
	//cout << A << endl;
	//TIME_START
	padding_forCDataBlob(A, A_pad, rowA, colA, pad_h, pad_w, channel);
	show_CData(A_pad);
	//for (int i = 0; i < 201; i++) {
	////	cout << A_pad.data[i] << ", ";
	////}
	//TIME_END("padding")

	CDataBlob<float> convert_A;
	convert_A.create(1, 1, rowC * colC* 3 * 3 * channel);
	//TIME_START
	convertA_forCDataBlob(A_pad, convert_A,rowC,colC,channel,pad_h,pad_w);
	show(rowC * colC, 3 * 3 * channel, convert_A.data);
	//TIME_END("convertA");
//
//	int num_filters = 1;
//	//CDataBlob<float>C;
//	//C.create(rowC * colC, num_filters, 32);
//	//C.setZero();
//	Filters<float> kernel(channel, num_filters, false, false, true, false);
//	kernel.weights.create(num_filters, 9, channel);
//	memcpy(kernel.weights.ptr(0, 0), k, sizeof(float) * 9 * channel);
//	//for (int ch = 0; ch < channel; ch++) {
//	//	for (int c = 0; c < 9; c++) {
//	//		kernel.weights.ptr(0, c)[ch] = k[ch+c*8];
//	//	}
//	//}
//	//show_CData(kernel.weights);
//	for (float i : k) {
//		cout << i << ", ";
//	}
//
//	//TIME_START
//
//	float d[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
//	
//	float* C = (float*)malloc((size_t)rowC * colC * num_filters*sizeof(float));
//	Matrixmul3d_blas_forCDataBlob(num_filters, d, k, C);
//	for (int i = 0; i < rowC*colC; i++) {
//		cout <<endl<< C[i] << ", ";
//	}
//TIME_END("padding")
	//show_CData(C);
	//TIME_END("blas");

	//CDataBlob<float>C_convert;
	//C_convert.create(rowC, colC, num_filters);
	////TIME_START
	//convertC_forCDatablob(C, C_convert);
	//TIME_END("total")

}

void main() {



	blas_Cdatablob_Test_forsure(3, 3, 32);



	//TIME_START
	//convertA_simd_test();
	//TIME_END("AS")
	//TIME_START
	//padding_32d_test();
	//TIME_END("test")

	////padding_test();
	////img2col();
	////CDataBlob<float> input,C;
	//blas_Cdatablob_Test(2048, 2048, 32);
	//ConvInfoStruct kernel1{ 32,32,false,false,true,false };
	//Filters<float> kernel;
	//kernel = kernel1;
	//////input.create(512, 512, 32*9);
	//////cout << "OK" << endl;
	//////C.create(32, 512*512, 1);
	//////cout << "OK1" << endl;
	//////int r = 32;
	//////int c = 512*512;
	//////int k = 32*9;
	//////TIME_START
	//////cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasConjNoTrans, r, c, k, 1, kernel.weights.data, 32*9, input.data, 512*512, 0, C.data, 512*512);
	//////TIME_END("openBlas")

	//CDataBlob<float> input1, output;
	//input1.create(2048, 2048, 32);
	////output.create(512, 512, 32);
	//TIME_START
	//convolution(input1, kernel, output, false);
	//TIME_END("CONV")
	//


}