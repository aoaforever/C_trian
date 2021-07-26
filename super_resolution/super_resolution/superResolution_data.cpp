#include"superResolution.h"

float f1_weight[3 * 32 * 1 * 1] = { 0,-1,0,-1,5,-1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,5,-1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,
									0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,5,-1,0,-1,0};
float f1_bias[3] = {0,0,0 };



//[channels,num_filters,is_depthwise,is_pointwise,with_relu,pWeight,pBiases]
ConvInfoStruct param_pConvInfo[1] = {
	{32,3,false,true,false,f1_weight,f1_bias}
};

