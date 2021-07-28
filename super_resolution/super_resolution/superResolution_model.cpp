#include"superResolution.h"
#include<stdio.h>
#include<string.h>

#define NUM_CONV_LAYER 2
#define test111 0



#include<opencv2/core/core.hpp>
#include<opencv2/core/mat.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
using namespace cv;
using namespace std;
#define compare(a) ((a)>=(255)?(255):((a)<(0)?(0):(a)))

extern ConvInfoStruct param_pConvInfo[NUM_CONV_LAYER];
Filters<float> g_pFilters[NUM_CONV_LAYER];

bool param_initialized = false;

void init_parameters() {
	for (int i = 0; i < NUM_CONV_LAYER; i++) {
		g_pFilters[i] = param_pConvInfo[i];
	}
}

void superResolution(unsigned char* rgbImageData, int width, int height, int step)
{
	CDataBlob<float> dataBlobs[NUM_CONV_LAYER+1];

	if (!param_initialized) {
#if test111
		std::cout << "doing param_initialized" << endl;
#endif
		init_parameters();
	}
	//convert Mat to CDataBlob
	dataBlobs[0].convertDatatoCDataBlob(rgbImageData, width, height, 3, step);

	//group convolution 3x3 
#if test111
	//std::cout << g_pFilters[0].weights;
	cout << dataBlobs[0];
#endif

	convolution(dataBlobs[0], g_pFilters[0], dataBlobs[1], false);
	convolution(dataBlobs[1], g_pFilters[1], dataBlobs[2], false);
#if test111
	//std::cout << g_pFilters[0].weights;
	cout << dataBlobs[1];
#endif

#if test111
	Mat result(dataBlobs[1].rows, dataBlobs[1].cols, CV_8UC3);
	for (int r = 0; r < result.rows; r++)
	{
		uchar* p = (uchar*)result.ptr(r);
		
		for (int c = 0; c < result.cols; c++)
		{
			for (int ch = 0; ch < result.channels(); ch++)
			{
				int idx = c * 3+ch;
				//cout << compare(dataBlobs[1].getElement(r, c, ch)) <<endl;
				p[idx] =compare(dataBlobs[1].getElement(r, c, ch));
				
			}

			//cout << endl;
		}
	}

	//imshow("aaa", result);
	//waitKey(0);
#endif
}
