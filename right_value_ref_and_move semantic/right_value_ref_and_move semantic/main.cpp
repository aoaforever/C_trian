#include <iostream>

using namespace std;

class Useless {
private:
	int n;//number of elements
	char* pc;// pointer to data
	static int ct;
	void ShowObject() const;
	//在类成员函数的声明和定义中，const的函数不能对其数据成员进行修改操作。const的对象，不能引用非const的成员函数。

public:
	Useless();//初始化？
	explicit Useless(int k);
	Useless(int k, char ch);
	Useless(const Useless& f);//regular copy constructor
	Useless(Useless&& f);//move constructor 移动语义
	~Useless();//析构函数
	Useless operator+(const Useless& f) const;
	//need operator=() in copy and move versions
	void ShowData()const;

};

//implementation
int Useless::ct = 0;

Useless::Useless() {
	++ct;
	n = 0;
	pc = nullptr;
	cout << "default constructor called.number of objects:" << ct << endl;
	ShowObject();
}

Useless::Useless(int k) :n(k) {
	++ct;
	cout << "int constructor called. number of objects : " << ct << endl;
	pc = new char[n];
	ShowObject();

}

Useless::Useless(int k, char ch) :n(k) {
	++ct;
	cout << "int ,char constructor called. number of objects :" << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; i++) {
		pc[i] = ch;

	}
	ShowObject();
}

Useless::Useless(const Useless& f) :n(f.n) {
	++ct;
	cout << "copy const called, number of objects: " << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; i++) {
		pc[i] = f.pc[i];//体现在这里拷贝
	}
	ShowObject();
}

Useless::Useless(Useless&& f) :n(f.n) {
	++ct;
	cout << "move constructor called, number of object: " << ct << endl;
	pc = f.pc;//steal address
	f.pc = nullptr;//这里为什么要这么干？
	f.n = 0;
	ShowObject();

}

Useless::~Useless() {
	cout << "destructor called; objects left: "<<--ct << endl;
	cout << "deleted object:\n";
	ShowObject();
	delete[] pc;
}


Useless Useless::operator+(const Useless& f)const {
	cout << "Entering operator+()\n";
	Useless temp = Useless(n + f.n);//call Useless(int k)
	for (int i = 0; i < n; i++) {
		temp.pc[i] = pc[i];
	}
	for (int i = n; i < temp.n; i++) {
		temp.pc[i] = f.pc[i - n];//将f的东西拼接到temp后面
	}

	cout << "temp object:\n";
	cout << "Leaving operator+()\n";
	return temp;
}


void Useless::ShowObject()const {
	cout << "number of elements: " << n;
	cout << " Data address: " << (void*)pc << endl;
}


void Useless::ShowData()const {
	if (n == 0)
		cout << "(Object empty)";
	else
		for (int i = 0; i < n; i++)
			cout << pc[i];
	cout << endl;
}

//application
int main() {
	{
		Useless one(10, 'x');
		Useless two = one;//call copy constructor
		Useless three(20, 'o');
		Useless four(one + three);//calls operator+(), move constructor
		cout << "Object one : ";
		one.ShowData();
		cout << "Object two : ";
		two.ShowData();
		cout << "Object three : ";
		three.ShowData();
		cout << "Object four : ";
		four.ShowData();


	}
}