#include<iostream>
#include<stdio.h>
#include<malloc.h>
//һ��charռ��8���ֽ�
using namespace std;
int main() {
	int* a;
	a = (int*)malloc( 10 * sizeof(int));
	if (a == NULL) {
		cout << "�ڴ����ʧ��" << endl;
		exit(1);
	}
	*a = 1;
	*(a + 1) = 2;
	*(a + 2)= 3;
	*(a + 3) = 4;

	std::cout <<"�����aָ��ĵ�һ���ڴ��ֵ: "<< * a << std::endl;
	cout << "���aָ��ָ��ĵ�ַ: " << a << endl;//a��ֵΪ�ڴ�ĵ�ַ��
	cout << "���a+1ָ��ĵ�ַ��" << a + 1 << endl;
	cout << "���ָ��a�ĵ�ַΪ��" << &a << endl;
	free(a);
	a = NULL;
	cout << "��aָ���֮��aָ��ĵ�ַ��ֵΪ��" << a << endl;

	//int a = 1;
	//int* p = &a;
	//int** q = &p;
	//cout << "a= " << a << endl;//a��ֵ
	//cout << "&a= " << &a << endl;//���a�ĵ�ַ
	//cout << "p= " << p << endl;//p��ֵ����pָ��ĵ�ַ��
	//cout << "*p= " << *p << endl;//pָ��ĵ�ַ���ط���������
	//cout << "&p= " << &p << endl;//���p�ĵ�ַ
	//cout << "q= " << q << endl;
	//cout << "*q= " << *q << endl;
	//cout << "**q= " << **q << endl;
	//cout << "&q= " << &q << endl;


	return 0;
}