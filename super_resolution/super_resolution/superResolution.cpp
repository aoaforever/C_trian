#include"superResolution.h"

#include <string.h>
#include <cmath>
#include <vector>
#include <float.h> //for FLT_EPSION
#include <algorithm>//for stable_sort, sort

void* myAlloc(size_t size) {
	char* ptr, * ptr0;
	ptr0 = (char*)malloc(
		(size_t)(size + _MALLOC_ALIGN * ((size >= 4096) + 1L) + sizeof(char*))
	);
	
	if (!ptr0)
		return 0;

	//align the pointer
	ptr = (char*)(((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1) & ~(size_t)(_MALLOC_ALIGN - 1));

	*(char**)(ptr - sizeof(char*)) = ptr0;
	return ptr;
}

void myFree_(void* ptr) {
	//Pointer must be algned by _MALLOC_ALIGN
	if (ptr)
	{
		if (((size_t)ptr & (_MALLOC_ALIGN - 1)) != 0)
			return;
		free(*((char**)ptr - 1));

	}
}

//p1 and p2 must be 512-bit aligned (16 float numbers)
inline float dotProduct(const float* p1, const float* p2, int num)
{
    float sum = 0.f;

#if defined(_ENABLE_AVX512)
    __m512 a_float_x16, b_float_x16;
    __m512 sum_float_x16 = _mm512_setzero_ps();
    for (int i = 0; i < num; i += 16)
    {
        a_float_x16 = _mm512_load_ps(p1 + i);
        b_float_x16 = _mm512_load_ps(p2 + i);
        sum_float_x16 = _mm512_add_ps(sum_float_x16, _mm512_mul_ps(a_float_x16, b_float_x16));
    }
    sum = _mm512_reduce_add_ps(sum_float_x16);
#elif defined(_ENABLE_AVX2)
    __m256 a_float_x8, b_float_x8;
    __m256 sum_float_x8 = _mm256_setzero_ps();
    for (int i = 0; i < num; i += 8)
    {
        a_float_x8 = _mm256_load_ps(p1 + i);
        b_float_x8 = _mm256_load_ps(p2 + i);
        sum_float_x8 = _mm256_add_ps(sum_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
    }
    sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
    sum_float_x8 = _mm256_hadd_ps(sum_float_x8, sum_float_x8);
    sum = ((float*)&sum_float_x8)[0] + ((float*)&sum_float_x8)[4];
#elif defined(_ENABLE_NEON)
    float32x4_t a_float_x4, b_float_x4;
    float32x4_t sum_float_x4;
    sum_float_x4 = vdupq_n_f32(0);
    for (int i = 0; i < num; i += 4)
    {
        a_float_x4 = vld1q_f32(p1 + i);
        b_float_x4 = vld1q_f32(p2 + i);
        sum_float_x4 = vaddq_f32(sum_float_x4, vmulq_f32(a_float_x4, b_float_x4));
    }
    sum += vgetq_lane_f32(sum_float_x4, 0);
    sum += vgetq_lane_f32(sum_float_x4, 1);
    sum += vgetq_lane_f32(sum_float_x4, 2);
    sum += vgetq_lane_f32(sum_float_x4, 3);
#else
    for (int i = 0; i < num; i++)
    {
        sum += (p1[i] * p2[i]);
    }
#endif

    return sum;
}

inline bool vecMulAdd(const float* p1, const float* p2, float* p3, int num)
{
#if defined(_ENABLE_AVX512)
    __m512 a_float_x16, b_float_x16, c_float_x16;
    for (int i = 0; i < num; i += 16)
    {
        a_float_x16 = _mm512_load_ps(p1 + i);
        b_float_x16 = _mm512_load_ps(p2 + i);
        c_float_x16 = _mm512_load_ps(p3 + i);
        c_float_x16 = _mm512_add_ps(c_float_x16, _mm512_mul_ps(a_float_x16, b_float_x16));
        _mm512_store_ps(p3 + i, c_float_x16);
    }
#elif defined(_ENABLE_AVX2)
    __m256 a_float_x8, b_float_x8, c_float_x8;
    for (int i = 0; i < num; i += 8)
    {
        a_float_x8 = _mm256_load_ps(p1 + i);
        b_float_x8 = _mm256_load_ps(p2 + i);
        c_float_x8 = _mm256_load_ps(p3 + i);
        c_float_x8 = _mm256_add_ps(c_float_x8, _mm256_mul_ps(a_float_x8, b_float_x8));
        _mm256_store_ps(p3 + i, c_float_x8);
    }
#elif defined(_ENABLE_NEON)
    float32x4_t a_float_x4, b_float_x4, c_float_x4;
    for (int i = 0; i < num; i += 4)
    {
        a_float_x4 = vld1q_f32(p1 + i);
        b_float_x4 = vld1q_f32(p2 + i);
        c_float_x4 = vld1q_f32(p3 + i);
        c_float_x4 = vaddq_f32(c_float_x4, vmulq_f32(a_float_x4, b_float_x4));
        vst1q_f32(p3 + i, c_float_x4);
    }
#else
    for (int i = 0; i < num; i++)
        p3[i] += (p1[i] * p2[i]);
#endif

    return true;
}

inline bool vecAdd(const float* p1, float* p2, int num)
{
#if defined(_ENABLE_AVX512)
    __m512 a_float_x16, b_float_x16;
    for (int i = 0; i < num; i += 16)
    {
        a_float_x16 = _mm512_load_ps(p1 + i);
        b_float_x16 = _mm512_load_ps(p2 + i);
        b_float_x16 = _mm512_add_ps(a_float_x16, b_float_x16);
        _mm512_store_ps(p2 + i, b_float_x16);
    }
#elif defined(_ENABLE_AVX2)
    __m256 a_float_x8, b_float_x8;
    for (int i = 0; i < num; i += 8)
    {
        a_float_x8 = _mm256_load_ps(p1 + i);
        b_float_x8 = _mm256_load_ps(p2 + i);
        b_float_x8 = _mm256_add_ps(a_float_x8, b_float_x8);
        _mm256_store_ps(p2 + i, b_float_x8);
    }
#elif defined(_ENABLE_NEON)
    float32x4_t a_float_x4, b_float_x4, c_float_x4;
    for (int i = 0; i < num; i += 4)
    {
        a_float_x4 = vld1q_f32(p1 + i);
        b_float_x4 = vld1q_f32(p2 + i);
        c_float_x4 = vaddq_f32(a_float_x4, b_float_x4);
        vst1q_f32(p2 + i, c_float_x4);
    }
#else
    for (int i = 0; i < num; i++)
    {
        p2[i] += p1[i];
    }
#endif
    return true;
}

bool convolution_1x1pointwise(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData)
{//{32, 16, false, true, true, f0_weight, f0_bias},[16* 32 * 1 * 1]个数据
// #if defined(_OPENMP)
// #pragma omp parallel for
// #endif
    cout << "1x1 conv\n";
    for (int row = 0; row < outputData.rows; row++)
    {
        for (int col = 0; col < outputData.cols; col++)
        {
            float* pOut = outputData.ptr(row, col);
            const float* pIn = inputData.ptr(row, col);

            for (int ch = 0; ch < outputData.channels; ch++)
            {
                const float* pF = filters.weights.ptr(0, ch);
                pOut[ch] = dotProduct(pIn, pF, inputData.channels);
                pOut[ch] += filters.biases.data[ch];
            }
        }
    }
    cout << "1x1 conv done\n";
    return true;
}
bool convolution_3x3default(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData) {
    cout << "default conv\n";
    //set all elements in outputData to zeros
    outputData.setZero();

    //multi thread??
    //....
    //
    for (int row = 0; row < outputData.rows; row++) {
        int srcy_start = row - 1;
        int srcy_end = srcy_start + 3;/////////////////顺序不能乱！！！！！！！！！！！！！！！！！！！！！！！！
        srcy_start = MAX(0, srcy_start);
        srcy_end = MIN(srcy_end, inputData.rows );

        for (int col = 0; col < outputData.cols; col++) {
            int srcx_start = col - 1;
            int srcx_end = srcx_start + 3;///////////////顺序不能乱！！！！！！！！！！！！！！！！！！！
            srcx_start = MAX(0, srcx_start);
            srcx_end = MIN(srcx_end, inputData.cols);

            float* pData = outputData.ptr(row, col);

            for (int ch = 0; ch < filters.num_filters; ch++) {
                for (int r = srcy_start; r < srcy_end; r++) {
                    for (int c = srcx_start; c < srcx_end; c++) {
                        float* pInput = inputData.ptr(r, c);
                        int f_r = r - row + 1;
                        int f_c = c - col + 1;
                        int filter_idx = 3 * f_r + f_c;
                        float* pFilter = filters.weights.ptr(ch, filter_idx);
                        //printf("row=%d, col=%d, ch=%d, r=%d, c=%d, filter_idx=%d, inchannels=%d \n", row, col,ch, r, c, filter_idx,inputData.channels );
                        pData[ch] += dotProduct(pInput, pFilter, inputData.channels);
                        //pData[ch] += 1;
                    }
                }
                pData[ch] += filters.biases.data[ch];
            }
        }
    }
    cout << "default conv done\n";
    return true;


}
bool convolution_3x3depthwise(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData)
{
    //set all elements in outputData to zeros
    outputData.setZero();
    // #if defined(_OPENMP)
    // #pragma omp parallel for
    // #endif
    for (int row = 0; row < outputData.rows; row++)
    {
        int srcy_start = row - 1;
        int srcy_end = srcy_start + 3;
        srcy_start = MAX(0, srcy_start);
        srcy_end = MIN(srcy_end, inputData.rows);

        for (int col = 0; col < outputData.cols; col++)
        {
            int srcx_start = col - 1;
            int srcx_end = srcx_start + 3;
            srcx_start = MAX(0, srcx_start);
            srcx_end = MIN(srcx_end, inputData.cols);

            float* pOut = outputData.ptr(row, col);

            for (int r = srcy_start; r < srcy_end; r++)
                for (int c = srcx_start; c < srcx_end; c++)
                {
                    int filter_r = r - row + 1;
                    int filter_c = c - col + 1;
                    int filter_idx = filter_r * 3 + filter_c;
                    
                    vecMulAdd(inputData.ptr(r, c), filters.weights.ptr(0, filter_idx), pOut, filters.num_filters);
                }
            vecAdd(filters.biases.ptr(0, 0), pOut, filters.num_filters);
        }
    }
    return true;
}

bool relu(CDataBlob<float>& inputoutputData)
{
    if (inputoutputData.isEmpty())
    {
        cerr << __FUNCTION__ << ": The input data is empty." << endl;
        return false;
    }

    int len = inputoutputData.cols * inputoutputData.rows * inputoutputData.channelStep / sizeof(float);
    bool leakyrelu = true;
    float val = 0.1;

#if defined(_ENABLE_AVX512)
    __m512 a, bzeros;
    bzeros = _mm512_setzero_ps(); //zeros
    for (int i = 0; i < len; i += 16)
    {
        a = _mm512_load_ps(inputoutputData.data + i);
        a = _mm512_max_ps(a, bzeros);
        _mm512_store_ps(inputoutputData.data + i, a);
    }
#elif defined(_ENABLE_AVX2)
    __m256 a, bzeros,c,relu_val;
    relu_val = _mm256_set_ps(val, val, val, val, val, val, val, val);
    bzeros = _mm256_setzero_ps(); //zeros
    for (int i = 0; i < len; i += 8)
    {
        a = _mm256_load_ps(inputoutputData.data + i);
        a = _mm256_max_ps(a, bzeros);
        if (leakyrelu) {
            c = _mm256_load_ps(inputoutputData.data + i);
            c = _mm256_min_ps(c, bzeros);
            c = _mm256_mul_ps(c, relu_val);
            a = _mm256_add_ps(a, c);
        }

        _mm256_store_ps(inputoutputData.data + i, a);
    }
#else    
    for (int i = 0; i < len; i++)
        inputoutputData.data[i] *= (inputoutputData.data[i] > 0);
#endif

    return true;
}

bool convolution(CDataBlob<float>& inputData, Filters<float>& filters, CDataBlob<float>& outputData, bool do_relu)
{
    if (inputData.isEmpty() || filters.weights.isEmpty() || filters.biases.isEmpty())
    {
        cerr << __FUNCTION__ << ": The input data or filter data is empty" << endl;
        return false;
    }
    if (inputData.channels != filters.channels)
    {
        cerr << __FUNCTION__ << ": The input data dimension cannot meet filters." << "inputData.channels ="<< inputData.channels<<  "filters.channels ="<<filters.channels << endl;
        return false;
    }

    outputData.create(inputData.rows, inputData.cols, filters.num_filters);

    if (filters.is_pointwise && !filters.is_depthwise )
        convolution_1x1pointwise(inputData, filters, outputData);
    else if (!filters.is_pointwise && filters.is_depthwise )
        convolution_3x3depthwise(inputData, filters, outputData);
    else if (filters.is_3x3 )
        convolution_3x3default(inputData, filters, outputData);
    else
    {
        cerr << __FUNCTION__ << ": Unsupported filter type." << endl;
        return false;
    }

    if (do_relu)
        return relu(outputData);

    return true;
}
bool averagePooling(CDataBlob<float>& inputData, CDataBlob<float>& outputData) {
    if (inputData.isEmpty())
    {
        cerr << "__FUNCTION__" << ": The input data is empty." << endl;
        return false;
    }

    if (inputData.channels % 8 != 0) {
        cerr << "The input channels can't be divide by 8 totally. " << endl;
        return false;
    }
    outputData.create(1, 1, inputData.channels);
    outputData.setZero();
    float* pOut = outputData.ptr(0, 0);

    for (int r = 0; r < inputData.rows; r++) {
        for (int c = 0; c < inputData.cols; c++) {
            float* pIn = inputData.ptr(r, c);
            vecAdd(pIn, pOut, inputData.channels);

        }
    }
}

bool pixelShuffle(CDataBlob<float>& inputData, CDataBlob<float>& outputData, int up_scale) {
    int input_channels = inputData.channels;
    if (input_channels % (up_scale *up_scale) != 0) {
        cerr << "The input channels must be divide by up_scale**2 totally. " << endl;
        return false;
    }
    int output_channels = input_channels / (up_scale * up_scale);
    outputData.create(inputData.rows * 2, inputData.cols * 2, output_channels);
    
    for (int row = 0; row < inputData.rows; row++) {
        for (int col = 0; col < inputData.cols; col++) {
            const float* pIn = inputData.ptr(row, col);
            int pointr_start = row * up_scale;
            int pointr_end = pointr_start + up_scale;

            int pointc_start = col * up_scale;
            int pointc_end = pointc_start + up_scale;

            int ch = 0;
            for (int r = pointr_start; r < pointr_end; r++) {
                for (int c = pointc_start; c < pointc_end; c++) {
                    //cout << "r= " << r << endl << "c= " << c << endl;
                    float* pOut = outputData.ptr(r, c);
                    for (int outchannel = 0; outchannel < output_channels; outchannel++) {
                        pOut[outchannel] = pIn[outchannel*up_scale*up_scale+(ch)];
                    }
                    ch = ch + 1;
                }
            }

        }
    }
    cout << "PixelShuffle done" << endl;
    return true;
}

bool convolutionforsimpleblocks(CDataBlob<float>& inputData, 
    Filters<float>& filters1, Filters<float>& filters2, Filters<float>& filters3, Filters<float>& filters4,
    CDataBlob<float>& outputData, bool do_relu) {

    CDataBlob<float> tmp1,tmp2,tmp3;
    bool r1 = convolution(inputData, filters1, tmp1, do_relu);
    cout << "r1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n" << tmp1 << "\n\n\n\n\n\n\n\n\n\n";
    bool r2 = convolution(tmp1, filters2, tmp2, do_relu);
    bool r3 = convolution(tmp2, filters3, tmp3, do_relu);
    bool r4 = convolution(tmp3, filters4, outputData, do_relu);
    return r1 && r2 && r3 && r4;
}