#include<iostream>
using namespace std;



// 面试题3（二）：不修改数组找出重复的数字
// 题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至
// 少有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改输入的
// 数组。例如，如果输入长度为8的数组{2, 3, 5, 4, 3, 2, 6, 7}，那么对应的
// 输出是重复的数字2或者3。

int getDuplication1(const int* numbers, const int length)
{//构建了长度为n+1的辅助数组，空间复杂度为O(n)
    if(numbers==nullptr||length<=0)
    {
        return -1;
    }
    
    int* tmp = new int[length];
    for(int i = 0;i<length; i++)
    {   
        cout<<numbers[i]-1<<","<<i<<endl;
        if(tmp[numbers[i]-1]==numbers[i]) 
           {
               return numbers[i];
           }
        
        
        if(tmp[numbers[i]-1]==numbers[i]) 
           {
               return numbers[i];
           }
        tmp[numbers[i]-1]=numbers[i]; 
        
    }

    for(int i=0;i<length;i++){
        cout<<tmp[i]<<",";
    }
    cout<<endl;
    delete[] tmp;
    return 0;
}

void test222(){
    int num[5]={2,4,3,1,1};
    int length= sizeof(num)/sizeof(int);
    int a;
    a=getDuplication1(num,length);
    printf("%d",a);
}

//算法时间复杂度O(n)
int countRange(const int* numbers, int length, int start , int end){
    //二分查找是要有序的数组，因此1~n就是一个有序的数组，每次分半，去源数组中查找这一半出现的次数
    //对整个数组查找重复次数,给定一个区间，在这个区间内，查看出现的次数

    if( numbers == nullptr)
        return 0;
    int count =0;
    for(int i=0;i<length;i++){
        if(numbers[i]>=start&&numbers[i]<=end){
            ++count;
        }

    }
    return count;
}
//总时间复杂度O(logn * n),没有辅助数组，空间复杂度O(1)
int getDuplication(const int* numbers, int length){
    if(numbers==nullptr||length<=0)
        return -1;
    
    int start =1 ;
    int end = length-1;
    //算法时间复杂度O(logn)
    while(end>=start){//当end=start还找个屁
        //2分查找算法。。
        int middle =( ( end - start )>>1 )+start;//下面这三种都一样？
        //int middle = (start+end)/2;
	    //int middle1 =(start+end)>>1;

        int count = countRange(numbers,length,start,middle);

        //找机会返回重复的数，也是停止的机会
        if(end==start){
            if(count>1)
                return start;//返回的是重复的数字，此算法并不能找出所有的重复的数字。start表示的是1~n中的任意一个数字。这个数字在原数组中重复了。

            else 
                break;
        }
        
            

        if(count > (middle-start)+1)//如何数个数？
            end = middle;
        else
            start = middle+1;
        

    }
    return -1;
}



// ====================测试代码====================
void test(const char* testName, int* numbers, int length, int* duplications, int dupLength)
{
    int result = getDuplication(numbers, length);
    printf("result=%d",result);
    for(int i = 0; i < dupLength; ++i)
    {
        if(result == duplications[i])
        {
            std::cout << testName << " passed." << std::endl;
            return;
        }
    }
    std::cout << testName << " FAILED." << std::endl;
}

// 多个重复的数字
void test1()
{
    int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
    int duplications[] = { 2, 3 };
    test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个重复的数字
void test2()
{
    int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7 };
    int duplications[] = { 4 };
    test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最小的数字
void test3()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8 };
    int duplications[] = { 1 };
    test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最大的数字
void test4()
{
    int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8 };
    int duplications[] = { 8 };
    test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 数组中只有两个数字
void test5()
{
    int numbers[] = { 1, 1 };
    int duplications[] = { 1 };
    test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字位于数组当中
void test6()
{
    int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7 };
    int duplications[] = { 3 };
    test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 多个重复的数字
void test7()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 6 };
    int duplications[] = { 2, 6 };
    test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个数字重复三次
void test8()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 2 };
    int duplications[] = { 2 };
    test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 没有重复的数字
void test9()
{
    int numbers[] = { 1, 2, 6, 4, 5, 3 };
    int duplications[] = { -1 };
    test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 无效的输入
void test10()
{
    int* numbers = nullptr;
    int duplications[] = { -1 };
    test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}
