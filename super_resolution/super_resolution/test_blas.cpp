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

void main() {
	CDataBlob<float> input,C;

	ConvInfoStruct kernel1{ 32,32,false,false,true,false };
	Filters<float> kernel;
	kernel = kernel1;
	input.create(512, 512, 32*9);
	cout << "OK" << endl;
	C.create(32, 512*512, 1);
	cout << "OK1" << endl;
	int r = 32;
	int c = 512*512;
	int k = 32*9;
	TIME_START
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasConjNoTrans, r, c, k, 1, kernel.weights.data, 32*9, input.data, 512*512, 0, C.data, 512*512);
	TIME_END("SAS")

	CDataBlob<float> input1, output;
	input1.create(512, 512, 32);
	//output.create(512, 512, 32);
	TIME_START
	convolution(input1, kernel, output, false);
	TIME_END("CONV")

}