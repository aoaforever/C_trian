#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int main(){
    vector<int> a{2,3,21,4,52,3,5,6,3,876,45,6,32,45};
    // sort(a.begin(),a.end());//默认升序
    sort(a.begin(),a.end(),[](int &a, int &b){
        return a>b;
    });//默认升序

    struct cmp{
        bool operator()(const pair<int,int>&a, pair<int,int>&b){
            return a.second<b.second;//升序
        }
    };


    priority_queue<int> pq;
    priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> qq;

    for(int i = 0 ; i <a.size();i++){
        // cout<<i<<" ";
        pair<int,int> c{i,a[i]};
        // pq.push(i);
        qq.push(c);
    }

    // while(!pq.empty()){
    //     int c = pq.top();
    //     pq.pop();
    //     cout<<c<<" ";
    // }

    while(!qq.empty()){
        pair<int,int> c = qq.top();
        qq.pop();
        cout<<c.first<<" "<<c.second<<", ";
    }
    return 0;
}