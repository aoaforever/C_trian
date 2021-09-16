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
#include <typeinfo>//typeof
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
	bool is_3x3;
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

	bool convertDatatoCDataBlob(const unsigned char* imgData, int imgWidth, int imgHeight, int imgChannels, int imgWidthStep) {
		if (imgData == NULL)
		{
			cerr << "The input image data is null." << endl;
			return false;
		}
		if (typeid(float) != typeid(T))
		{
			cerr << "DataBlob must be float in the current version." << endl;
			return false;
		}
		if (imgChannels != 3)
		{
			cerr << "The input image must be a 3-channel RGB image." << endl;
			return false;
		}

		create(imgHeight, imgWidth, 32);
		setZero();

#if defined(_OPENMP)
#pragma omp parallel for
#endif
		for (int r = 0; r < this->rows; r++) {
			for (int c = 0; c < this->cols; c++) {
				T* pData = this->ptr(r, c);//指向输出图像的r行c列	

				for (int fy = -1; fy <= 1; fy++) {
					int srcy = r + fy;

					if (srcy < 0 || srcy >= imgHeight)
						continue;

					for (int fx = -1; fx <= 1; fx++)
					{
						int srcx = c + fx;

						if (srcx < 0 || srcx >= imgWidth)
							continue;

						const unsigned char* pImgData = imgData + srcy * size_t(imgWidthStep) + srcx*imgChannels;

						int output_channel_offset = ((fy + 1) * 3 + fx + 1);//如果滤波器在图像之外，则之外的元素偏置为0.
						pData[output_channel_offset] = pImgData[2]/255.0;
						pData[output_channel_offset+9] = pImgData[1]/255.0;//一个3x3有9个元素
						pData[output_channel_offset+18] = pImgData[0]/255.0;
					}
				}
				
			}
		}
		return true;
	}


	inline T getElement(int r, int c, int ch) {
		if (this->data)
		{
			if (r >= 0 && r < this->rows &&
				c >= 0 && c < this->cols &&
				ch >= 0 && ch < this->channels)
			{
				T* p = this->ptr(r, c);
				return p[ch];
			}
		}

		return (T)(0);
	}

	friend ostream& operator<<(ostream& output, CDataBlob &dataBlob) {
		output << "DataBlob Size (channels, rows, cols) = ("
			<< dataBlob.channels << ", "
			<< dataBlob.rows << ", "
			<< dataBlob.cols << ", "
			<< ")" << endl;

		if (dataBlob.rows * dataBlob.cols * dataBlob.channels <= 64)
		{
			//print the elements only when the total number is less than 16
			for (int ch = 0; ch < dataBlob.channels; ch++) {
				output << "Channel " << ch << ": " << endl;

				for (int r = 0; r < dataBlob.rows; r++)
				{
					output << "(";

					for (int c = 0; c < dataBlob.cols; c++) {
						T* p = dataBlob.ptr(r, c);

						if (sizeof(T) < 4) {
							output << (int)(p[ch]);
						}
						else {
							output << p[ch];
						}

						if (c != dataBlob.cols - 1)
							output << ", ";

					}
					output << ")" << endl;
				}
			}
		}
		else {
			for (int ch = 0; ch < dataBlob.channels; ch++) {
				output << ch<<" channel= (\n" << dataBlob.getElement(0, 0, ch) << "\t" << dataBlob.getElement(0, 1, ch) << " ... " << dataBlob.getElement(0, dataBlob.cols - 1, ch) << endl
					<< dataBlob.getElement(1, 0, ch) << "\t" << dataBlob.getElement(1, 1, ch) << " ... " << dataBlob.getElement(1, dataBlob.cols - 1, ch) << endl
					<< " , ..., " << endl
					<< dataBlob.getElement(dataBlob.rows - 1, 0, ch) << "\t" << dataBlob.getElement(dataBlob.rows - 1, 1, ch) << " ... " << dataBlob.getElement(dataBlob.rows - 1, dataBlob.cols - 1, ch) << endl

					<< " )" << endl;
			}
		}
		return output;
	}

};

template <typename T>
class Filters {
public:
	int channels;//input_channels;
	int num_filters;//output_channels;
	bool is_depthwise;//3x3
	bool is_pointwise;//1x1
	bool is_3x3;
	bool with_relu;
	CDataBlob<T> weights;
	CDataBlob<T> biases;

	Filters() {
		channels = 0;
		num_filters = 0;
		is_depthwise = false;
		is_pointwise = false;
		is_3x3 = false;
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
		this->is_3x3 = convinfo.is_3x3;
		this->with_relu = convinfo.with_relu;

		if (!this->is_depthwise && this->is_pointwise&&!this->is_3x3) {
			this->weights.create(1, num_filters, channels);
			this->weights.setZero();
		}//1x1

		else if (this->is_depthwise && !this->is_pointwise&&!this->is_3x3) {
			this->weights.create(1, 9, channels);
			this->weights.setZero();
		}//3x3 group conv
		else if (!this->is_depthwise && !this->is_pointwise && this->is_3x3)
		{
			this->weights.create(num_filters, 9, channels);
			this->weights.setZero();
		}
		else {
			cerr << "Unsupported filter type. Only 1x1 point-wise and 3x3 depth-wise are supported." << endl;
			return *this;
		}

		this->biases.create(1, 1, num_filters);//有多少个滤波器就有多少个偏差
		this->biases.setZero();
		//
		//if (!this->is_3x3) {
		//	//开始拷贝卷积参数到filters中
		//	for (int fidx = 0; fidx < this->weights.cols; fidx++) {
		//		memcpy(this->weights.ptr(0, fidx),
		//			convinfo.pWeighhts + fidx * channels,
		//			sizeof(T) * channels);

		//	}
		//}
		//else if (this->is_3x3) {
		//	for (int r = 0; r < this->weights.rows; r++) {
		//		for (int c = 0; c < this->weights.cols; c++) {
		//			int filter_dix_inByte = (r * this->weights.cols + c) * this->channels;
		//			memcpy(this->weights.ptr(r, c),
		//				convinfo.pWeighhts + filter_dix_inByte,
		//				sizeof(T) * channels);
		//		}
		//	}
		//}
		//
		//memcpy(this->biases.ptr(0, 0),
		//	convinfo.pBiases,
		//	sizeof(T) * this->num_filters);

		return *this;
	}
};

bool convolution(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData, bool do_relu = true);
bool pixelShuffle(CDataBlob<float>& inputData, CDataBlob<float>& outputData, int up_scale);
float superResolution(unsigned char* rgbImageData, int width, int height, int step);
bool convolutionforsimpleblocks(CDataBlob<float>& inputData, Filters<float>& filters1, Filters<float>& filters2, Filters<float>& filters3, Filters<float>& filters4,
	CDataBlob<float>& outputData, bool do_relu = true);
bool PixelAdd(CDataBlob<float>& inputData, CDataBlob<float>& outputData);