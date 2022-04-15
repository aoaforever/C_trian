#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <numeric>
#include <future>

using namespace std;
int sum=0;
mutex mu;
condition_variable cv;
void to_sum(vector<int>::iterator begin,vector<int>::iterator end){
    this_thread::sleep_for(chrono::seconds(4));
    int res = accumulate(begin,end,0);
    unique_lock<mutex> lock(mu);
    sum = res;
    lock.unlock();
    cv.notify_one();
}

void to_sum2(vector<int>::iterator begin,vector<int>::iterator end,promise<int> p){
    this_thread::sleep_for(chrono::seconds(4));
    int res = accumulate(begin,end,0);
    p.set_value(res);//将结果存入，并让共享状态变为就绪以提醒future
    
}

int to_sum3(vector<int>::iterator begin, vector<int>::iterator end){
    this_thread::sleep_for(chrono::seconds(4));
    int res = accumulate(begin,end,0);
    return res;
}

int main(){
    vector<int> a{1,2,3,4,5,6};
    // thread mythread(to_sum,a.begin(),a.end());
    // unique_lock<mutex> lock(mu);
    // cv.wait(lock,[]{return sum;});//唤醒加锁后，先判断sum被改变了没有，没有的话继续睡眠
    // // cv.wait(lock);
    // cout<<sum<<endl;
    // lock.unlock();
    // mythread.join();

    // promise<int> p;
    // future<int> f = p.get_future();
    // thread mythread(to_sum2,a.begin(),a.end(),move(p));
    // f.wait();//等待结果

    // cout<<"result= "<<f.get()<<endl;
    // mythread.join();
    // //发出一个线程异步执行求和

    auto f = std::async(std::launch::async,to_sum3,a.begin(),a.end());
    cout<<f.get()<<endl;
    return 0;
}