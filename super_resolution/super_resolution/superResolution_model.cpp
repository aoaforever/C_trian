#include"superResolution.h"
#include<stdio.h>
#include<string.h>

#define NUM_CONV_LAYER 42
#define test111 1
#define test1112 1



#include<opencv2/core/core.hpp>
#include<opencv2/core/mat.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
using namespace cv;
using namespace std;
#define compare(a) ((a)>=(255)?(255):((a)<(0)?(0):(a)))

#if 1
cv::TickMeter cvtm;
#define TIME_START cvtm.reset();cvtm.start();
#define TIME_END(FUNCNAME) cvtm.stop(); printf(FUNCNAME);printf("=%gms\n", cvtm.getTimeMilli());

#else
#define TIME_START
#define TIME_END(FUNCNAME)
#endif



extern ConvInfoStruct param_pConvInfo[NUM_CONV_LAYER];
Filters<float> g_pFilters[NUM_CONV_LAYER];
void show(CDataBlob<float>& dataBlobs) {
	int val = 13;
	
	Mat result2(dataBlobs.rows, dataBlobs.cols, CV_8UC3);
	Mat image(dataBlobs.rows, dataBlobs.cols, CV_8UC3);
	//cout << dataBlobs.rows << " and " << dataBlobs.cols << " and " << dataBlobs.channels << endl;
	for (int r = 0; r < result2.rows; r++)
	{
		
		for (int c = 0; c < result2.cols; c++)
		{
			
			for (int ch = 0; ch < result2.channels(); ch++)
			{
				int idx = c * 2 + ch;
		
				////cout << compare(dataBlobs[1].getElement(r, c, ch)) <<endl;
				//p1[idx] =compare(dataBlobs[1].getElement(r, c, ch));
				result2.at<Vec3b>(r,c)[ch] = compare(dataBlobs.getElement(r, c, 2 - ch) * 255.0);
			}

			////cout << endl;
		}
	}
	image = result2;
	//cout << "image.channels=" << image.channels() << endl;
	for (int ch = 0; ch < image.channels(); ch++) {
		cout << "The after output \n" << ch << " channel= (\n" << (int)image.at<Vec3b>(0, 0)[ch] << "\t" << (int)image.at<Vec3b>(0, 1)[ch] << " ... " << (int)image.at<Vec3b>(0, image.cols - 1)[ch] << endl
			<< (int)image.at<Vec3b>(1, 0)[ch] << "\t" << (int)image.at<Vec3b>(1, 1)[ch] << " ... " << (int)image.at<Vec3b>(1, image.cols - 1)[ch] << endl
			<< " , ..., " << endl
			<< (int)image.at<Vec3b>(image.rows - 1, 0)[ch] << "\t" << (int)image.at<Vec3b>(image.rows - 1, 1)[ch] << " ... " << (int)image.at<Vec3b>(image.rows - 1, image.cols - 1)[ch] << endl

			<< " )" << endl;
	}
	//namedWindow("conv1", 0);
	namedWindow("conv2", 0);
	//resizeWindow("conv1", dataBlobs[1].cols / 1.8, dataBlobs[1].rows / 1.8);
	//resizeWindow("conv2", dataBlobs[2].cols / 1.8, dataBlobs[2].rows / 1.8);

	//imshow("conv1", result1);
	//imwrite("./srx2.png", result2);
	imshow("conv2", result2);
	//waitKey(0);
}

bool param_initialized = false;

void init_parameters() {
	for (int i = 0; i < NUM_CONV_LAYER; i++) {
#if test1112
		//cout << i <<" filter" << endl;
#endif
		g_pFilters[i] = param_pConvInfo[i];
	}
}

float superResolution(unsigned char* rgbImageData, int width, int height, int step)
{
	cv::TickMeter cvtm;
	
	CDataBlob<float> dataBlobs[14];

	if (!param_initialized) {
#if test1112
		//cout << "doing param_initialized" << endl;
#endif
		TIME_START
		init_parameters();
		param_initialized = true;
		TIME_END("init param")
	}
	//cvtm.reset();
	//cvtm.start();
	//convert Mat to CDataBlob
	TIME_START
	dataBlobs[0].convertDatatoCDataBlob(rgbImageData, width, height, 3, step);
	//cout << dataBlobs[0] << endl;
	TIME_END("convert")

	//head
	//cout << "head conv\n";
	TIME_START
	convolution(dataBlobs[0], g_pFilters[0], dataBlobs[1], false);
	TIME_END("convert conv")
	////cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\nhead conv\n" << dataBlobs[1] << "\n\n\n\n\n\n";
	//show(dataBlobs[1]);
	//cout << "head conv done\n";
	//simple_blocks x10
	//cout << "simple_blocks x10 conv\n";
	TIME_START
	//int temp = 1;
	//for(int i =1;i<=10;i++){
	//	//cout << i <<"," << temp << ", " << temp + 1 << ',' << temp + 2 << ',' << temp + 3 << ", " << i + 1 << endl;
	//	convolutionforsimpleblocks(dataBlobs[i], g_pFilters[temp], g_pFilters[temp +1], g_pFilters[temp +2], g_pFilters[temp +3], dataBlobs[i+1], true);
	//	PixelAdd(dataBlobs[i], dataBlobs[i + 1]);
	//	
	//	////cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n 1个 simple_blocks \n" << dataBlobs[1] << "\n\n\n\n\n\n";
	//	////cout << dataBlobs[i] << endl << endl;
	//	temp = temp+4;//1111111111111111111111111111111111111111111111111111
	//}
	convolutionforsimpleblocks(dataBlobs[1], g_pFilters[1], g_pFilters[2], g_pFilters[3], g_pFilters[4], dataBlobs[2], true);
	PixelAdd(dataBlobs[1], dataBlobs[2]);
	convolutionforsimpleblocks(dataBlobs[2], g_pFilters[5], g_pFilters[6], g_pFilters[7], g_pFilters[8], dataBlobs[3], true);
	PixelAdd(dataBlobs[2], dataBlobs[3]);
	convolutionforsimpleblocks(dataBlobs[3], g_pFilters[9], g_pFilters[10], g_pFilters[11], g_pFilters[12], dataBlobs[4], true);
	PixelAdd(dataBlobs[3], dataBlobs[4]);
	convolutionforsimpleblocks(dataBlobs[4], g_pFilters[13], g_pFilters[14], g_pFilters[15], g_pFilters[16], dataBlobs[5], true);
	PixelAdd(dataBlobs[4], dataBlobs[5]);
	convolutionforsimpleblocks(dataBlobs[5], g_pFilters[17], g_pFilters[18], g_pFilters[19], g_pFilters[20], dataBlobs[6], true);
	PixelAdd(dataBlobs[5], dataBlobs[6]);
	convolutionforsimpleblocks(dataBlobs[6], g_pFilters[21], g_pFilters[22], g_pFilters[23], g_pFilters[24], dataBlobs[7], true);
	PixelAdd(dataBlobs[6], dataBlobs[7]);
	convolutionforsimpleblocks(dataBlobs[7], g_pFilters[25], g_pFilters[26], g_pFilters[27], g_pFilters[28], dataBlobs[8], true);
	PixelAdd(dataBlobs[7], dataBlobs[8]);
	convolutionforsimpleblocks(dataBlobs[8], g_pFilters[29], g_pFilters[30], g_pFilters[31], g_pFilters[32], dataBlobs[9], true);
	PixelAdd(dataBlobs[8], dataBlobs[9]);
	convolutionforsimpleblocks(dataBlobs[9], g_pFilters[33], g_pFilters[34], g_pFilters[35], g_pFilters[36], dataBlobs[10], true);
	PixelAdd(dataBlobs[9], dataBlobs[10]);
	convolutionforsimpleblocks(dataBlobs[10], g_pFilters[37], g_pFilters[38], g_pFilters[39], g_pFilters[40], dataBlobs[11], true);
	PixelAdd(dataBlobs[10], dataBlobs[11]);


	TIME_END("10 simple_blocks")
	//cout << "simple_blocks x10 conv done\n";
	//cout << "before pix conv\n";
	TIME_START
	convolution(dataBlobs[11], g_pFilters[41], dataBlobs[12], false);	
	TIME_END("上采样前卷积花费")
	////cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n上采样前\n" << dataBlobs[12] << "\n\n\n\n\n\n";
	//cout << "before pix conv done\n";
	//cout << "pixelShuffle doing\n";
	TIME_START
	pixelShuffle(dataBlobs[12], dataBlobs[13], 2);
	TIME_END("up")
	////cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n上采样后\n" << dataBlobs[13] << "\n\n\n\n\n\n";
	//cout << "pixelShuffle doing done\n";
	//pixelShuffle(dataBlobs[1], dataBlobs[2], 2);
	//convolution(dataBlobs[1], g_pFilters[1], dataBlobs[2], false);
	cvtm.stop();
	show(dataBlobs[13]);
	return cvtm.getTimeMilli();
}
