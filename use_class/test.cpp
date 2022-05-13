#include <iostream>

using namespace std;

// class A{
// public:
//     void func();
// };

// //this鎸囬拡鐨勮皟鏁?
// class A{
// public: 
//     int a;
//     A(){
//         printf("A::A()的this指针是%p!\n",this);
//     }
//     void funcA(){
//         printf("A:funcA()的this指针是%p!\n",this);
//     }
// };

// class B {
// public:  
//     int b;  
//     B(){
//        printf("B::B()的this指针是%p!\n", this);  
//     }  
//     void funcB(){
//         printf("B::funcB()的this指针是%p!\n", this);  
//     }
// };

// class C: public A, public B
// {
// public:
//     int c;
//     C(){
//         printf("C::C()的this指针是%p!\n",this);
//     }
//     void funcC(){
//         printf("C::funcC()的this指针是%p!\n",this);
//     }
//     // void funcB(){
//     //     printf("C::funcB()的this指针是%p!\n",this);
//     // }
// };


//类的构造函数
//编译器会在哪些必要的时候帮助我们把默认的构造函数合成出来呢？
//(1)这里类C没有任何构造函数，但包含一个类B类型的成员变量mb,而该对象ma所属于的类B有一个缺省的构造函数。这个时候，编译器就会为该类C生成一个 “合成默认的构造函数”，合成的目的是为了调用B里的默认构造函数。
// class A{
// public:
//     A(){
//         //默认构造函数
//         cout<<"A"<<endl;
//     }
// };

// class B{
// public:
//     B(){
//         // 默认构造函数
//         cout<<"B"<<endl;
//     }
// };

// class C{
// public:
//     int m_i;
//     int m_j;
//     B mb;//类类型成员变量，因为构建了B类型成员变量，因此会调用B的构造函数
//     void func(){
//         cout<<"C::func()"<<endl;
//     }
// };

// //  (2)父类带缺省构造函数，子类没有任何构造函数，那因为父类这个缺省的构造函数要被调用，所以编译器会为这个子类合成出一个默认构造函数。    
// //合成的目的是为了调用这个父类的构造函数。换句话说，编译器合成了Child类默认的构造函数，并在其中安插代码，调用其父类base的缺省构造函数。
// class base{
// public:
//     base(){
//         cout<<"base()"<<endl;
//     }
// };

// class child:public base{
// public:
//     int a;
//     int b;
//     child(){
//         cout<<"child()"<<endl;
//     }
// };

//（3）如果一个类含有虚函数，但没有任何构造函数时,需要合成构造函数。     
//编译器会给我们生成一个基于该类的虚函数表vftable。然后编译给我们合成了一个构造函数，并且在其中安插代码：把类的虚函数表地址赋给类对象的虚函数表指针 （赋值语句/代码）。
class Base {
public:
    Base(){
        cout<<"Base()"<<endl;
    }
};

class Child:public Base{
public:
    int a=1;
    int b=2;
    void funct(){
        cout<<"funct()"<<endl;
    }

    virtual void mvirfunc(){
        cout<<"mvirfunc"<<endl;
    }
};


//内存对齐
typedef struct stu{
    //对齐基数：1,2,4,8,16
    //在没有#pragma pack宏的情况下，一般默认对齐基数为8
    char c1;//1
    int n;//4
    float f;//4
    char c2;//1
}stu;//10

int main(){
    // cout<<sizeof(A);//1

    // //this指针的调整
    // A a;
    // a.funcA();
    // B b;
    // b.funcB();
    // cout<<endl;
    // C c;
    // c.funcC();
    // c.funcB();
    // c.funcA();

    //类的构造函数

    // A a;
    // B b;
    // C c;

    // child d;//先调用父类的构造函数，在调用子类的构造函数

    // Child e;

    //内存对齐
    stu s;
    cout<<sizeof(s)<<endl;


}