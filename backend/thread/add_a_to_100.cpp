#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
using namespace std;
class Lock{
private:
    mutex m;
public:
    void lock(){
        m.lock();
    }
    void unlock(){
        m.unlock();
    }
};
//声明
class Solution{
public:
    int num_threads;
    vector<thread> t1;
    Lock m1;
    int a;
    Solution(int n){
        a=0;
        num_threads = n;
        t1.resize(num_threads);
    }
    // static void worker(void* argc);
    void dothread(){
        auto lamba_func = [&]()->void {
            while(true){
                m1.lock();
                if(a>=100) {
                    m1.unlock();
                    break;
                }
                a++;
                cout<<endl<<this_thread::get_id()<<" "<<a<<endl;
                m1.unlock();
                this_thread::sleep_for(chrono::seconds(2));
            }
        };
        for(int i=0;i<num_threads;i++){
            //循环创建线程
            t1[i] = thread(lamba_func);
        }
        for(int i=0;i<num_threads;i++){
            //等待线程结束
            t1[i].join();
        }
        // t1 = thread(worker,this);
        // t2 = thread(worker,this);
        // t1.join();
        // t2.join();
    }

    // void run(){
    //     //对a++;
    //     while(true){
    //         m1.lock();
    //         if(a>=100) {
    //             m1.unlock();
    //             break;
    //         }
    //         a++;
    //         cout<<endl<<this_thread::get_id()<<" "<<a<<endl;
    //         m1.unlock();
    //         this_thread::sleep_for(chrono::seconds(2));
    //     }
    // };
};
// void Solution::worker(void* argc){
//     Solution* s = (Solution*)argc;
//     s->run();
// }
int main(){
    


    Solution s(10);
    s.dothread();
    return 0;
}