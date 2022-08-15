#include <thread>
#include <mutex>
#include <vector>
#include <iostream>


using namespace std;

char a='a';
mutex mu;
void print(){
  
    while (1)
    {
        {
            std::lock_guard<mutex> gmutex(mu);
            if(a>=('z'+1)){
                
                break;
            }

            cout<<this_thread::get_id()<<"  "<<a<<endl;
            a++;

            // mu.unlock();
            // gmutex.~lock_guard();//所以必须在睡眠前释放锁，不然整个逻辑就是串行的。
            // 又或者，手动添加一个域，来确保raii的过期释放。
        }

	    this_thread::sleep_for(chrono::seconds(2));
    }
}


int main(int argc, char const *argv[])
{
    vector<thread> pool(3);
    for(int i=0;i<3;i++){
        pool[i] = thread(print);
    }

    for(int i=0;i<3;i++){
        pool[i].join();
    }

    return 0;
}
