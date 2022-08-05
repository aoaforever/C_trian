#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class A {
public:
	virtual void func1() { cout << "A::func1" << endl; }
private:
	int _a;
};

class B :public A{
public:
	virtual void func1() { cout << "B::func1" << endl; }
	virtual void func2() { cout << "B::func2" << endl; }
private:
	int _b;
};
class C :public A{
public:
	virtual void func1() { cout << "C::func1" << endl; }
	virtual void func2() { cout << "C::func2" << endl; }
private:
	int _c;
};
class D : public B, public C {
public:
	virtual void func1() { cout << "D::func1" << endl; }
	virtual void func3() { cout << "D::func3" << endl; }
private:
	int _d;
};

typedef void(*VFPTR)();//虚函数指针
void Print(VFPTR *arr)
{
	for (int i = 0; arr[i] != nullptr; ++i)
	{
		printf("第%d个虚函数地址：%0x\n",i, arr[i]);
		arr[i]();
	}
}

int main()
{
	D d;
	VFPTR* arr1 = (VFPTR*)(*(int*)&d);//虚表指针(虚函数指针数组)
	VFPTR* arr2 = (VFPTR*)(*(((int*)&d)+3));//第二个虚表指针偏移量
	Print(arr1);
	Print(arr2);
	return 0;
}	
