#include <iostream>

using namespace std;

// class A{
// public:
//     void func();
// };

// //this指针的调�?
// class A{
// public: 
//     int a;
//     A(){
//         printf("A::A()��thisָ����%p!\n",this);
//     }
//     void funcA(){
//         printf("A:funcA()��thisָ����%p!\n",this);
//     }
// };

// class B {
// public:  
//     int b;  
//     B(){
//        printf("B::B()��thisָ����%p!\n", this);  
//     }  
//     void funcB(){
//         printf("B::funcB()��thisָ����%p!\n", this);  
//     }
// };

// class C: public A, public B
// {
// public:
//     int c;
//     C(){
//         printf("C::C()��thisָ����%p!\n",this);
//     }
//     void funcC(){
//         printf("C::funcC()��thisָ����%p!\n",this);
//     }
//     // void funcB(){
//     //     printf("C::funcB()��thisָ����%p!\n",this);
//     // }
// };


//��Ĺ��캯��
//������������Щ��Ҫ��ʱ��������ǰ�Ĭ�ϵĹ��캯���ϳɳ����أ�
//(1)������Cû���κι��캯����������һ����B���͵ĳ�Ա����mb,���ö���ma�����ڵ���B��һ��ȱʡ�Ĺ��캯�������ʱ�򣬱������ͻ�Ϊ����C����һ�� ���ϳ�Ĭ�ϵĹ��캯�������ϳɵ�Ŀ����Ϊ�˵���B���Ĭ�Ϲ��캯����
// class A{
// public:
//     A(){
//         //Ĭ�Ϲ��캯��
//         cout<<"A"<<endl;
//     }
// };

// class B{
// public:
//     B(){
//         // Ĭ�Ϲ��캯��
//         cout<<"B"<<endl;
//     }
// };

// class C{
// public:
//     int m_i;
//     int m_j;
//     B mb;//�����ͳ�Ա��������Ϊ������B���ͳ�Ա��������˻����B�Ĺ��캯��
//     void func(){
//         cout<<"C::func()"<<endl;
//     }
// };

// //  (2)�����ȱʡ���캯��������û���κι��캯��������Ϊ�������ȱʡ�Ĺ��캯��Ҫ�����ã����Ա�������Ϊ�������ϳɳ�һ��Ĭ�Ϲ��캯����    
// //�ϳɵ�Ŀ����Ϊ�˵����������Ĺ��캯�������仰˵���������ϳ���Child��Ĭ�ϵĹ��캯�����������а�����룬�����丸��base��ȱʡ���캯����
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

//��3�����һ���ຬ���麯������û���κι��캯��ʱ,��Ҫ�ϳɹ��캯����     
//�����������������һ�����ڸ�����麯����vftable��Ȼ���������Ǻϳ���һ�����캯�������������а�����룺������麯�����ַ�����������麯����ָ�� ����ֵ���/���룩��
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


//�ڴ����
typedef struct stu{
    //���������1,2,4,8,16
    //��û��#pragma pack�������£�һ��Ĭ�϶������Ϊ8
    char c1;//1
    int n;//4
    float f;//4
    char c2;//1
}stu;//10

int main(){
    // cout<<sizeof(A);//1

    // //thisָ��ĵ���
    // A a;
    // a.funcA();
    // B b;
    // b.funcB();
    // cout<<endl;
    // C c;
    // c.funcC();
    // c.funcB();
    // c.funcA();

    //��Ĺ��캯��

    // A a;
    // B b;
    // C c;

    // child d;//�ȵ��ø���Ĺ��캯�����ڵ�������Ĺ��캯��

    // Child e;

    //�ڴ����
    stu s;
    cout<<sizeof(s)<<endl;


}