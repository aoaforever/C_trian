//mutex1.cpp 通过互斥体lock与unlock保护共享全局变量
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::chrono::milliseconds interval(100);

std::mutex mut;
int job_shared = 0;//两个线程都能修改，mutex将保护此变量
int job_exclusive =0;//只有一个线程能修改，不需要保护

//此线程只能修改job_shared.
void job1(){
    mut.lock();
    this_thread::sleep_for(5*interval);//令其持锁等待
    ++job_shared;
    cout<<"job1 shared("<<job_shared<<")\n";
    mut.unlock();
}

//此线程能修改job_shared和job_exclusive
void job2(){
    while(true){//无线循环，直到获得锁并修改job_shared
        if(mut.try_lock()){//尝试获得锁成功则修改job_shared
            ++job_shared;
            cout<<"job2 shared("<<job_shared<<")\n";
            mut.unlock();
            return;
        }
        else{//尝试获得锁失败，接着修改job_exclusive
            ++job_exclusive;
            cout<<"job2 exclusive("<<job_exclusive<<")\n";
            this_thread::sleep_for(interval);
        }
    }
}

int main(){
    thread thread1(job1);
    thread thread2(job2);

    thread1.join();
    thread2.join();

    system("pause");

    return 0;
}