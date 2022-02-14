#include <queue>
#include <iostream>

using namespace std;

template<class T>
class My_stack{
public:
    void push(const T& val){
        a.push(val);
        top_val = val;//记录最后一个元素就是栈顶元素
    };
    T top(){//返回栈顶元素
        return top_val;
    };
    void pop(){//弹出栈顶元素
        int size = a.size();
        while(size>2){//留下最后两个元素
            a.push(a.front());
            a.pop();
            --size;
        }
        //记录新的队尾元素
        top_val = a.front();
        a.push(a.front());
        a.pop();

        //弹出栈顶
        a.pop();
    };
    bool empty(){//判断栈是否为空
        return a.empty();
    };
private:
    queue<T> a;//队列只有front()函数
    T top_val;
};

int main(){
    My_stack<int> stack;
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);

    while (!stack.empty())
    {
        cout<<stack.top()<<" ";
        stack.pop();
    }
    

    return 0;
}