//condition_variable.cpp用互斥锁实现一个生产者消费者模型


#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

queue<int> q;//队列全局变量
mutex mu;//互斥锁全局变量
condition_variable cond;//全局条件变量

//生产者，往队列中放入数据
void function_1(){
    int count =10;
    while(count>0){
        unique_lock<mutex> locker(mu);
        q.push(count); //数据入队锁保护
        locker.unlock();
        cond.notify_one();//像一个等待线程发出“条件以满足”的通知
        this_thread::sleep_for(chrono::seconds(1));//延时一秒
        count--;
    }
}

//消费者，从队列提取数据
void function_2(){
    int data=0;
    while(data!= 1){
        unique_lock<mutex> locker(mu);
        if(!q.empty()){
            data=q.front();
            q.pop();
            locker.unlock();
            cout<<"t2 got a value from t1: "<<data<<endl;
        }
        else{
            locker.unlock();
        }

        
    }
}

//消费者，从队列提取数据
void function_3(){
    int data=0;
    while(data!= 1){
        unique_lock<mutex> locker(mu);
        while (q.empty())//判断队列是否为空
        {
            cond.wait(locker);//解锁互斥量，并陷入休眠以等待通知被唤醒，被唤醒后加锁以保护共享数据
        }

        data = q.front();
        q.pop();
        locker.unlock();
        cout<<"t3 got a value from t1: "<<data<<endl;
    }
}

int main(){

    thread t1(function_1);
    thread t2(function_2);
    // thread t3(function_3);   

    t1.join();
    t2.join();
    // t3.join();

    system("pause");
    return 0;
}