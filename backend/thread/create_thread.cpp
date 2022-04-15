#include <iostream>
#include <thread>

using namespace std;
void thread_function(int n){
    for(int i =0; i<5;i++){ 
        cout<<"Child function thread"<<this_thread::get_id()<<" running "<<i<<endl;
        this_thread::sleep_for(chrono::seconds(n));
    }
}
class Thread_functor{
public:
    void operator()(int n){//怎么传参数？
        for(int i =0; i<5;i++){
            cout<<"Child functor thread"<<this_thread::get_id()<<" running "<<i<<endl;
            this_thread::sleep_for(chrono::seconds(n));
        }
    }
};

int main(){
    std::thread mythread1(thread_function,1);
    mythread1.join();//等待子线程结束，主线程在结束         

    Thread_functor thread_functor;
    thread mythread2(thread_functor,3);
    mythread2.detach();

    auto thread_lambda = [](int n){
            for(int i =0; i<5;i++){
                cout<<"Child lambda thread"<<this_thread::get_id()<<" running "<<i<<endl;
                this_thread::sleep_for(chrono::seconds(n));
            }
    };
    thread mythread3(thread_lambda,4);
    mythread3.join();


    for(int i =0; i<5;i++){
            cout<<"Main function thread"<<this_thread::get_id()<<" running "<<i<<endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

    
    cout<<"EXIT!"<<endl;

    system("pause");
    return 0;
}