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
void show(const int row, const int col, const float* mat) {
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cout << mat[r * col + c] << ", ";
		}
		cout << endl;
	}
}
void show_3d(const int channel, const int row, const int col, const float* mat) {
	for (int ch= 0; ch < channel; ch++) {
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

void padding_3d(const int pad_h, const int pad_w,const int rowA, const int colA, const int channel, float* A_pad, const float* A) {
	//一个通道有多少个偏移量？ 对A来说，c*rowA*colA+r*colA+j
	//对A_pad来说， c*pad_w*pad_h+r*pad_w+j
	for (int ch = 0; ch < channel; ch++) {
		for (int r = 0; r < pad_h; r++) {
			for (int c = 0; c < pad_w; c++) {
				int col = ch * pad_w * pad_h + r * pad_w + c;//其实就是偏移量了啦

				if (r == 0 || r == pad_h - 1) {
					A_pad[col] = 0;
				}
				else {
					if (c == 0 || c == pad_w - 1) {
						A_pad[col] = 0;
					}
					else {
						A_pad[col] = A[ch * rowA * colA + (r - 1) * colA + c - 1];
					}
				}
			}
		}
	}
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

void Matrixmul3d_blas(const int convAh, const int convAw,const int channel,const int num_filters, float* A_convert, float* B_convert, float* C) {
	const enum CBLAS_ORDER order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasTrans;
	const int M = convAh;//A的行数，C的行数
	const int N = num_filters;//B的列数，C的列数
	const int K = convAw*channel;//A的列数，B的行数
	const float alpha = 1;
	const float beta = 0;
	const int lda = K;
	const int ldb = K;
	const int ldc = N;

	cblas_sgemm(order, TransA, TransB, M, N, K, alpha, A_convert, lda, B_convert, ldb, beta, C, ldc);



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

void convertA_3d(float* A_convert, const int rowC,const int colC, const int convAw, const int pad_h ,const int pad_w, float* A_pad, const int channel)
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
void convertB_3d(float* B_convert, const int filters, const int channel,const int kernel, const float* B) {
	for (int r = 0; r < filters; r++) {
		int ptr = r * kernel * kernel * channel;
		memcpy(B_convert+ptr, B+ptr,sizeof(float)*((size_t)kernel*kernel*channel));
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

void padding_3d_test() {
	const int pad = 1;
	const int stride = 1;

	//定义A三维
	const int rowA = 3;
	const int colA = 4;
	const int channel = 3;
	const float A[channel * rowA * colA] = {
		1,2,3,4,
		2,3,4,5,
		3,4,5,6,
	

		100,2,3,4,
		2,3,4,5,
		3,4,5,6,
	

		200,2,3,4,
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

		100,1,1,
		1,1,1,
		2,2,2,

		3,3,3,
		3,2,3,
		4,3,5,

		2,3,4,
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
	//show(convAh, convAw * channel, A_convert);
	
	const int rowK = num_filters;
	const int colK = kernel * kernel * channel;
	float B_convert[rowK * colK];
	convertB_3d(B_convert, num_filters, channel, kernel, B);
	show(rowK, colK, B_convert);

	//记得转置卷积核的展开B_convert
	float C[convAh*num_filters];
	Matrixmul3d_blas(convAh, convAw, channel, num_filters, A_convert, B_convert, C);

	float C_convert[rowC * colC * num_filters];
	convertC_3d(C_convert, convAh, num_filters, C);
	show_3d(num_filters, rowC, colC, C_convert);
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
	padding_3d_test();
	//padding_test();
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