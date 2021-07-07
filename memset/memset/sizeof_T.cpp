


#include <iostream>
#include <bitset>
using namespace std;


typedef struct a {
	char a;
	char b;
	char c;
	int d;
}A;
int main() {
	//cout << "sizeof(float)= " << sizeof(float) << endl;//4
	//cout << "sizeof(int)= " << sizeof(int) << endl;//4
	//cout << "sizeof(double)= " << sizeof(double) << endl;//8
	//cout << "sizeof(char)= " << sizeof(char) << endl;//1
	//cout << "sizeof(char*)= " << sizeof(char*) << endl;//8
	//cout << "sizeof(int*)= " << sizeof(int*) << endl;//8
	//cout << "sizeof(float*)= " << sizeof(float*) << endl;//8
	//cout << "sizeof(double*)= " << sizeof(double*) << endl;//8
	////cout << 24 % 32 << endl;
	//cout << bitset<64>(~size_t(256 - 1)) << endl;
	//cout << bitset<64>(size_t(256 - 1)) << endl;
	////cout << size_t(10) << endl;
	cout << sizeof(A) << endl;


	return 0;
}