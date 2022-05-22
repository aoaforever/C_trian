#pragma once    
#include <pthread.h>
#include <list>
#include "locker.h"
using namespace std;
template <class T>
class threadpool{
private:
    const static int MAX_THREADS =8;
    pthread_t *threads;
    void run();
    static void *worker(void* arg);
    list<T*> queue;
    locker queue_locker;
    sem queuestat;
public:
    bool append(T* request){
        //将请求放到请求队列里。
        queue_locker.lock();
        queue.push_back(request);
        queue_locker.unlock();
        queuestat.post();
        return true;
    }

    threadpool(){
        threads = new pthread_t[MAX_THREADS];
        for(int i=0;i<MAX_THREADS;i++){
            if(pthread_create(threads+i,NULL,worker,this)!=0){
                perror("创建线程错误\n");
                delete [] threads;
                exit(1);

            }

            if(pthread_detach(threads[i])){
                delete [] threads;
                exit(1);
            }
        }
    }
    ~threadpool(){
        delete[] threads;
    }

};

template <class T>
void* threadpool<T>::worker(void* arg){
    threadpool* pool =(threadpool*)arg;
    pool->run();
    return pool;
}

template< class T>
void threadpool<T>::run(){
    while(true){
        queuestat.wait();
        queue_locker.lock();
        if(queue.empty()){
            queue_locker.unlock();
            continue;
        }

        T * request = queue.front();
        queue.pop_back();
        queue_locker.unlock();

        if(!request){
            continue;
        }

        // cout<<"recv "<<isize<<" bytes from "<<request->fd<<": "<<string(request->buf)<<endl;
        // //读完后，往写缓冲区写入东西，并注册写事件，通知主循环去对内核缓冲区写东西
        request->process();
    }
}