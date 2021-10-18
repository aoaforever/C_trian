#include <iostream>
#include <cstring>
//为下面添加一个赋值运算符函数

class CMyString
{
private: 
    char* m_pData;
public:
    CMyString(char * pData=nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);
    void Print();
//1.能连续赋值
//2.避免调用复制构造函数
//3.不能改变传入实例的状态
//4.是否释放自身已有的内存。
//5.判断传入的参数和当前的实例（*this）是不是同一个实例。

    CMyString& operator=(const CMyString& str);
};

CMyString::CMyString(char* pData){
    if (pData==nullptr){
        m_pData=new char[1];
        m_pData[0]='\0';
    }
    else{
    m_pData=new char[strlen(pData)+1];
    strcpy(m_pData,pData);
    }
}

CMyString::CMyString(const CMyString&str){
    m_pData=new char[strlen(str.m_pData)+1];
    strcpy(m_pData,str.m_pData);
}

CMyString::~CMyString(){
    delete []m_pData;
}
CMyString& CMyString::  operator=(const CMyString&str){//返回类型写在最前面
    //书里还有异常安全性代码
    //5
    if(&str == this){
        return *this;
    }

    //4
    delete []m_pData;
    m_pData=nullptr;

    m_pData=new char[strlen(str.m_pData)+1];
    strcpy(m_pData,str.m_pData);
    return *this;
    
}


//测试代码
void CMyString::Print()
{
    printf("%s", m_pData);
}
void Test1()
{
    printf("Test1 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}
int main(int argc , char * argv[])
{
    Test1();
    Test2();
    Test3();

    return 0 ;
}