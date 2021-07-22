#include"superResolution.h"

float f1_weight[3 * 1 * 3 * 3] = { 0,-1,0,-1,5,-1,0,-1,0,0,-1,0,-1,5,-1,0,-1,0, 0,-1,0,-1,5,-1,0,-1,0 };
float f1_bias[3] = { 0,0,0 };

ConvInfoStruct param_pConvInfo[1] = {
	{3,3,true,false,false,f1_weight,f1_bias}
};

