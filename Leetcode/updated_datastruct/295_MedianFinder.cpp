#include <queue>
using namespace std;

class MedianFinder {
private:
struct cmp{
    bool operator()(int a, int b){
        // return a<b;//less，小于，升序，在优先队列中就是大的在顶部   
        return a>b;//greater，大于，降序序，在优先队列中就是小的在顶部

    }
};
    priority_queue<int> large;
    priority_queue<int,vector<int>,cmp> small;
public:

    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(small.size()<large.size()){
            large.push(num);
            small.push(large.top());
            large.pop();
        }
        else {
            small.push(num);
            large.push(small.top());
            small.pop();
        }
        
    }
    
    double findMedian() {
        //  如果元素不一样多,多的那个的堆顶元素就是中位数
        if(small.size()>large.size()){
            return small.top();
        }
        else if(small.size()<large.size()){
            return large.top();
        }
        else {
            return (small.top()+large.top())/2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */