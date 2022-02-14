#include <stack>
#include <cstdio>
#include <iostream>
using namespace std;

template <class T>
class My_queue{
    //b做队尾，a做队头
public:
    void push(const T& val){
        b.push(val);
    };
    T top(){//获取队头元素
        if(a.empty()){
            while(!b.empty()){
                a.push(b.top());
                b.pop();
            }
        }

        return a.top();
    }

    void pop(){//删除队头元素
        top();
        a.pop();
    };

    bool empty(){//判断两个栈是否为空
        return (a.empty()&&b.empty());
    };

private:
    stack<T> a;
    stack<T> b;
    
};


int main(){
    My_queue<int> queue;
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);

    while (!queue.empty())
    {
        cout<<queue.top()<<" ";
        queue.pop();
    }
    

    return 0;
}