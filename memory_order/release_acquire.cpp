#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>
using namespace std;

atomic<string*> ptr;
int data;

void producer(){
    string* p = new string("hello");
    ptr.store(p,memory_order_release);
    data =43;
}

void consumer(){
    string* p2;
    while(!(p2 = ptr.load(memory_order_acquire)));
    assert(*p2=="hello");// 绝无问题
    assert(data=43);// 绝无问题
}

int main(){
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}

