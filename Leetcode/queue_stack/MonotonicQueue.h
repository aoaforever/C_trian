#include <queue>
#include <list>
using namespace std;

class MonotonicQueue{
private:
    list<int> q;

public:
    void push(int n){
        //将前面小于自己的元素都删除
        while(!q.empty() && q.back() < n){
            q.pop_back();
        }

        q.push_back(n);
    }
    int max(){
        //队头的元素肯定是最大的
        return q.front();
    }

    //pop()方法在队头删除元素n,也很好写
    void pop(int n){
        if(n == q.front()){
            q.pop_front();
        }
    }




};