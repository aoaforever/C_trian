#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
不安全的实现方式：

原因：考虑当两个线程同时调用 getInstance 方法，并且同时检测到 instance 是 NULL，两个线程会同时实例化对象，不符合单例模式的要求。

懒汉模式：直到第一次用到类的实例时才去实例化，上面是懒汉实现。
*/

class Singleton{
private:
    Singleton(){};//默认构造函数
    Singleton(const Singleton& a){};//拷贝构造函数
    Singleton& operator=(const Singleton& tmp){};//赋值构造函数
    static Singleton* instance;
public:
    void print(){
        cout<<this<<endl;
    }
    static Singleton* getInstance(){
        if(instance==nullptr){
            if(instance==nullptr){
                instance = new Singleton();
            }
        }       
        return instance; 
    }
};

Singleton* Singleton::instance =nullptr;//static变量需要在类外面初始化

/*
C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
在C++11标准下，《Effective C++》提出了一种更优雅的单例模式实现，使用函数内的 local static 对象。
这样，只有当第一次访问getInstance()方法时才创建实例。
这种方法也被称为Meyers' Singleton。C++0x之后该实现是线程安全的，C++0x之前仍需加锁。
*/
// class Singleton{
// private:
//     Singleton(){};//默认构造函数
//     Singleton(const Singleton& a){};//拷贝构造函数
//     Singleton& operator=(const Singleton& tmp){};//赋值构造函数
    
// public:
//     void print(){
//         cout<<this<<endl;
//     }
//     static Singleton* getInstance(){
//         static Singleton instance;    
//         cout<<"构造 "<<&instance<<endl;
//         return &instance;
//     }
// };


int main(){
    //既然只有一个实例，那就可以直接这么调用。
    Singleton::getInstance()->print();

    Singleton* p1 = Singleton::getInstance();
    cout<<p1<<endl;
    p1->print();
    Singleton* p2 = Singleton::getInstance();
    p2->print();

    

    // a.getInstance();
    // cout<<&a<<endl;
}