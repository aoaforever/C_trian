#include<iostream>
#include <cstdio>
//寻找数组中重复的数字
// 面试题3（一）：找出数组中重复的数字
// 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
// 那么对应的输出是重复的数字2或者3。

//传入数组，长度，重复的数字
//返回bool
bool  duplicate(int numbers[], int length, int* duplication)
{
    printf("asdasd");
    //错误类型判断
    if(numbers==nullptr||length<=0)
    {
        return false;
    }

    //数字范围在0~n-1范围内,长度为n
    for ( int i =0;i<length;i++)
    {
        if(numbers[i]<0||numbers[i]>=length)
            return false;
    }

    //开始算法
    for (int i =0; i < length; i++ ){
        //当下标指向的元素值不等于该下标值时
        while(numbers[i]!= i){
            
            //发现重复的元素
            if(numbers[i]==numbers[numbers[i]])
            {
                *duplication = numbers[i];
                return true;
            }
            
            //交换
            int temp = numbers[i];
            numbers[i]=numbers[numbers[i]];
            numbers[numbers[i]]=temp;
            //或者numbers[temp]=temp;

        }

        

    }
    //当所有下标指向的元素值都等于该下标值时，返回false,表示没有重复的数字
    return false;

}

//代码中尽管有一个 两重循环，但每个数字最多只要交换两次就能找到属于它自己的位置，因此总的时间复杂度时O(n)。
//另外，所有的操作步骤都是在输入数组上进行的，不需要额外分配内存，因此空间复杂度时O（1）
// ====================测试代码====================
bool contains(int array[], int length, int number)
{
    for(int i = 0; i < length; ++i)
    {
        if(array[i] == number)
            return true;
    }

    return false;
}

void test(char* testName, int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument)
{
    printf("%s begins: ", testName);

    int duplication;
    bool validInput = duplicate(numbers, lengthNumbers, &duplication);

    if(validArgument == validInput)
    {
        if(validArgument)
        {
            if(contains(expected, expectedExpected, duplication))
                printf("Passed.\n");
            else
                printf("FAILED.\n");
        }
        else
            printf("Passed.\n");
    }
    else
        printf("FAILED.\n");
}

// 重复的数字是数组中最小的数字
void test1()
{
    int numbers[] = { 2, 1, 3, 1, 4 };
    int duplications[] = { 1 };
    test("Test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 重复的数字是数组中最大的数字
void test2()
{
    int numbers[] = { 2, 4, 3, 1, 4 };
    int duplications[] = { 4 };
    test("Test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 数组中存在多个重复的数字
void test3()
{
    int numbers[] = { 2, 4, 2, 1, 4 };
    int duplications[] = { 2, 4 };
    test("Test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 没有重复的数字
void test4()
{
    int numbers[] = { 2, 1, 3, 0, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test("Test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 没有重复的数字
void test5()
{
    int numbers[] = { 2, 1, 3, 5, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test("Test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 无效的输入
void test6()
{
    int* numbers = nullptr;
    int duplications[] = { -1 }; // not in use in the test function
    test("Test6", numbers, 0, duplications, sizeof(duplications) / sizeof(int), false);
}

int main()
{
    test1();

    return 0;
}