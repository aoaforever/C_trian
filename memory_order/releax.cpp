#include <atomic>
#include <vector>
#include <thread>
#include <iostream>
using namespace std;
/*
宽松内存顺序的典型使用是计数器自增，
例如 std::shared_ptr 的引用计数器，
因为这只要求原子性，但不要求顺序或同步
（注意 std::shared_ptr 计数器自减要求与析构函数进行获得释放同步）

*/
atomic<int> cnt = {0};//我有一个计数器，初始值为0
atomic<char> p = {'a'};
void func(){
    for(int i=0;i<1000;i++){
        cnt.fetch_add(1,std::memory_order_relaxed);
    }
}

void print(){
    while(1){
        char cur = p.load(memory_order_seq_cst);
        if(cur>'z') break;
        cout<<cur<<endl;
        p.fetch_add(1,memory_order_seq_cst);
    }
    
}
int main(){
    vector<thread> pool;
    auto start = chrono::steady_clock::now();
    for(int i=0;i<10;i++){
        pool.emplace_back(thread(print));
    }
    
    for(auto& p :pool){
        p.join();
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> spend = end-start;
    cout<<cnt<<"  spend: "<<spend.count()*1e3<<"ms"<<endl;
    return 0;
}


