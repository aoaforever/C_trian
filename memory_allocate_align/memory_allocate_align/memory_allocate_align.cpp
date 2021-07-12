#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <malloc.h>
//void* aligned_malloc(size_t required_bytes, size_t aligned)
//{
//	int offset = aligned - 1;
//	void* p = (void*)malloc(required_bytes + offset);
//	void* q = (void*)(((size_t)(p)+offset) & ~(aligned - 1));
//	return q;
//
//}


using namespace std;
void* myAlloc(size_t size);
void myFree_(void* ptr);
#define myFree(ptr) (myFree_(*(ptr)), *(ptr)=0);
#define _MALLOC_ALIGN 256
//
//void setNULL()
//{
//    if (data)
//        myFree(&data);
//    //rows = cols = channels = channelStep = 0;
//}

void* myAlloc(size_t size)
{
    char* ptr, * ptr0;
    cout << "size + _MALLOC_ALIGN * ((size >= 4096) + 1L = " << (size + _MALLOC_ALIGN * ((size >= 4096) + 1L)) << endl;
    cout << "sizeof(char*)= " << sizeof(char*) << endl;
    cout << "分配大小=" << (size_t)(size + _MALLOC_ALIGN * ((size >= 4096) + 1L) + sizeof(char*)) << endl;
    ptr0 = (char*)malloc(
        (size_t)(size + _MALLOC_ALIGN * ((size >= 4096) + 1L) + sizeof(char*)));

    if (!ptr0)
        return 0;
    cout << "ptr0= " << (size_t)ptr0 << endl;//1F798115B90
    cout << "((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1)= " << ((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1) << endl;
    cout << "~(size_t)(_MALLOC_ALIGN - 1)= " << ~(size_t)(_MALLOC_ALIGN - 1) << endl;
    cout << "(((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1) & ~(size_t)(_MALLOC_ALIGN - 1))= " << (((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1) & ~(size_t)(_MALLOC_ALIGN - 1)) << endl;

    // align the pointer
    ptr = (char*)(((size_t)(ptr0 + sizeof(char*) + 1) + _MALLOC_ALIGN - 1) & ~(size_t)(_MALLOC_ALIGN - 1));
    printf("ptr=%p\n", ptr);
    printf("ptr0=%p\n", ptr0);
    printf("(ptr - sizeof(char*))=%p\n", (char**)(ptr - sizeof(char*)));
    *(char**)(ptr - sizeof(char*)) = ptr0;

    return ptr;
}

void myFree_(void* ptr)
{
    // Pointer must be aligned by _MALLOC_ALIGN
    if (ptr)
    {
        if (((size_t)ptr & (_MALLOC_ALIGN - 1)) != 0)
            return;
        free(*((char**)ptr - 1));
    }
}

using namespace cv;
int main(void)
{
    ////简单的指针对齐,但是可能编译器自动就帮你对齐好了
    //float c[4] = { 1,2,3,4 };
    //float* p = c;
    //float* q = NULL;
    //float n = 4;
    //printf("p=%p\nq=%p\n", p, q);
    //q = alignPtr<float>(p);
    //printf("p=%p\nq=%p\n", p, q);



    int* o, *g =NULL;
    o = (int*)malloc(1000 * sizeof(int*));
    cout << "sizeof(int*)= " << sizeof(int*) << endl;
    cout << sizeof(o) << endl;
    printf("o=%p\n", o);
    printf("o+1= %p\n", o + 1);

    g = alignPtr(o, 256);
    printf("g=%p\n", g);
    /*
    o = 000001F409AB8020
    o + 1 = 000001F409AB8024
    g= 000001F409AB8100
    o+255=      11111010000001001101010111000000100011111
    -256=       11111111111111111111111111111111100000000
    按位与之后： 11111010000001001101010111000000100000000=1F409AB8100=g*/
    free(o);

    return 0;

    ///*cout << ((0x000F) & (0xFFF0)) << endl;*/
    //double* p1 = (double*)malloc(10 * sizeof(double));
    //printf("default-aligned addr:   %p\n", (void*)p1);
    //cout << p1 + 2 << endl;
    //cout << (size_t)p1 + 2 << endl;
    //free(p1);

    //int* p2 = (int*)_aligned_malloc(256, 256 * sizeof(int));
    //printf("1024-byte aligned addr: %p\n", (void*)p2);
    //_aligned_free(p2);


   // int rows = 10;
   // int cols = 10;
   // int channels = 3;
   // int channelStep;
   // float* data;

   // int remBytes = (sizeof(float) * channels) % (_MALLOC_ALIGN / 8);
   // cout << "remBytes= " << remBytes << endl;

   // if (remBytes == 0)
   //     channelStep = channels * sizeof(float);
   // else
   //     channelStep = (channels * sizeof(float)) + (_MALLOC_ALIGN / 8) - remBytes;
   // data = (float*)myAlloc(size_t(rows) * cols * channelStep);

   // if (data == NULL)
   // {
   //     cerr << "Failed to alloc memeory for uint8 data blob: "
   //         << rows << "*"
   //         << cols << "*"
   //         << channels << endl;
   //     return false;
   // }

   // myFree(&data);//#define myFree(ptr) (myFree_(*(ptr)), *(ptr)=0);
   ///* myFree_(*(&data));
   // *(&data) = 0;*/


   // // 100111111010010011111100010110100001011000  dec:2742671206488  0x27E93F16858
   // // 111111111111111111111111111111111100000000  dec:4398046510848  0x3FFFFFFFF00
   // // 100111111010010011111100010110100000000000  dec:2742671206400  0x27E93F16800
   // //保证低8位全是0.即能够地址能够被256整除。
}