#include"superResolution.h"
#include<stdio.h>
#include<string.h>

#define NUM_CONV_LAYER 1

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
	CDataBlob<float> dataBlobs[2];

	if (!param_initialized)
		init_parameters();

	//convert Mat to CDataBlob
	dataBlobs[0].convertDatatoCDataBlob(rgbImageData, width, height, 3, step);

	//group convolution 3x3 
	convolution(dataBlobs[0], g_pFilters[0], dataBlobs[1], false);

}
