#include<iostream>
#include<stdio.h>
#include<malloc.h>
//一个char占用8个字节
using namespace std;
int main() {
	int* a;
	a = (int*)malloc( 10 * sizeof(int));
	if (a == NULL) {
		cout << "内存分配失败" << endl;
		exit(1);
	}
	*a = 1;
	*(a + 1) = 2;
	*(a + 2)= 3;
	*(a + 3) = 4;

	std::cout <<"仅输出a指向的第一个内存的值: "<< * a << std::endl;
	cout << "输出a指针指向的地址: " << a << endl;//a的值为内存的地址：
	cout << "输出a+1指向的地址：" << a + 1 << endl;
	cout << "存放指针a的地址为：" << &a << endl;
	free(a);
	a = NULL;
	cout << "令a指向空之后，a指向的地址的值为：" << a << endl;

	//int a = 1;
	//int* p = &a;
	//int** q = &p;
	//cout << "a= " << a << endl;//a的值
	//cout << "&a= " << &a << endl;//存放a的地址
	//cout << "p= " << p << endl;//p的值，即p指向的地址。
	//cout << "*p= " << *p << endl;//p指向的地址（地方）的内容
	//cout << "&p= " << &p << endl;//存放p的地址
	//cout << "q= " << q << endl;
	//cout << "*q= " << *q << endl;
	//cout << "**q= " << **q << endl;
	//cout << "&q= " << &q << endl;


	return 0;
}