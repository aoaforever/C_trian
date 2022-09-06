//单例模式
#include <iostream>
using namespace std;

class ab{
public:
    static ab* getinstance(){
        static ab m_a;
        return &m_a;
    }
    void print(){
        cout<<"hahaha"<<endl;
    }
private:
    ab(){};
    ab(const ab& a){};
    ab& operator=(const ab& a){};//注意返回引用
};

int main(){
    ab* a = ab::getinstance();
    ab* b = ab::getinstance();
    cout<<a<<endl<<b<<endl;;
    a->print();
    return 0;
}