#pragma once


#define _ENABLE_AVX2 1

#if defined(_ENABLE_AVX512)||defined(_ENABLE_AVX2)
#include<immintrin.h>
#endif

#if defined(_ENABLE_AVX2)
#define _MALLOC_ALIGN 256
#endif

#if defined(_ENABLE_AVX512)&& defined(_ENABLE_AVX2)
#error Cannot enable the two of AVX512 and AVX2 at the same time.
#endif

#if defined(_OPENMP)
#include <omp.h>
#endif

//包含 一些 常用库
#include <iostream>//cerr
#include <string.h>//memcpy

using namespace std;

void* myAlloc(size_t size);
void myFree_(void* ptr);
#define myFree(ptr) (myFree_(*(ptr)), *(ptr)=0);

#ifndef MIN
# define MIN(a,b) ((a)>(b)?(b):(a))
#endif // !MIN

#ifndef MAX
#define MAX(a,b) ((a)<(b)?(b):(a))
#endif


typedef struct ConvInfoStruct_ {
	int channels;//input_channels
	int num_filters;//output_channels
	bool is_depthwise;
	bool is_pointwise;
	bool with_relu;
	float* pWeighhts;
	float* pBiases;
}ConvInfoStruct;

template<typename T>
class CDataBlob
{
public:
	T* data;
	int rows;
	int cols;
	int channels;//the numbers of channels of one elements
	int channelStep;//how many memory one elments take in byte.

public:
	CDataBlob() {
		data = 0;
		rows = 0;
		cols = 0;
		channels = 0;
		channelStep = 0;
	}

	CDataBlob(int r, int c, int ch) {
		data = 0;
		create(r, c, ch);
	}

	~CDataBlob() {
		setNULL();
	}

	void setNULL()
	{
		if (data)
			myFree(&data);
		rows = cols = channels = channelStep = 0;
	}

	void setZero()
	{
		if (data)
			memset(data, 0 ,channelStep * rows * cols);
	}

	inline bool isEmpty() {
		return (rows <= 0 || cols <= 0 || channels == 0 || data == NULL);
	}

	bool create(int r, int c, int ch) {
		setNULL();

		rows = r;
		cols = c;
		channels = ch;

		//alloc space  for int8 array
		int remBytes = (sizeof(T) * channels) % (_MALLOC_ALIGN / 8);
		if (remBytes == 0)
			this->channelStep = channels * sizeof(T);
		else
			this->channelStep = (channels * sizeof(T)) + (_MALLOC_ALIGN / 8) - remBytes;
		data = (T*)myAlloc(size_t(rows) * cols * this->channelStep);

		if (data == NULL)
		{
			cerr << "Failed to alloc memeory for uint8 data blob: "
				<< rows << "*"
				<< cols << "*"
				<< channels << endl;
			return false;
		}

		return true;
	}

	inline T* ptr(int r, int c) {//用于指向图像某位置的指针
		if (r < 0 || r >= this->rows || c < 0 || c >= this->cols)
			return NULL;

		return (this->data + (size_t(r) * this->cols + c) * this->channelStep / sizeof(T));

	}



};

template <typename T>
class Filters {
public:
	int channels;//input_channels;
	int num_filters;//output_channels;
	bool is_depthwise;//3x3
	bool is_pointwise;//1x1
	bool with_relu;
	CDataBlob<T> weights;
	CDataBlob<T> biases;

	Filters() {
		channels = 0;
		num_filters = 0;
		is_depthwise = false;
		is_pointwise = false;
		with_relu = true;
	}

	//init the Filters
	Filters& operator=(ConvInfoStruct& convinfo)
	{
		if (typeid(float) != typeid(T))
		{
			cerr << "The data type must be float in this version." << endl;
			return *this;
		}


		if (typeid(float*) != typeid(convinfo.pWeighhts) ||
			typeid(float*) != typeid(convinfo.pBiases))
		{
			cerr << "The data type of the filter parameters must be float in this version." << endl;
			return *this;
		}

		this->channels = convinfo.channels;
		this->num_filters = convinfo.num_filters;
		this->is_depthwise = convinfo.is_depthwise;
		this->is_pointwise = convinfo.is_pointwise;
		this->with_relu = convinfo.with_relu;

		if (!this->is_depthwise && this->is_pointwise) {
			this->weights.create(1, num_filters, channels);
		}//1x1

		else if (this->is_depthwise && !this->is_pointwise) {
			this->weights.create(1, 9, channels);
		}//3x3 group conv
		else {
			cerr << "Unsupported filter type. Only 1x1 point-wise and 3x3 depth-wise are supported." << endl;
			return *this;
		}

		this->biases.create(1, 1, num_filters);//有多少个滤波器就有多少个偏差

		//开始拷贝卷积参数到filters中
		for (int fidx = 0; fidx < this->weight.cols; fidx++) {
			memcpy(this->weights.ptr(0, fidx),
				convinfo.pWeighhts + fidx * channels,
				sizeof(T) * channels);
			
		}
		memcpy(this->biases.ptr(0, 0),
			convinfo.pBiases,
			sizeof(T) * this->num_filters);

		return *this;
	}
};

bool convolution(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData, bool do_relu = true);
