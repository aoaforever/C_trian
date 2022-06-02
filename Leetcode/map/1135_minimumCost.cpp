#include "Union_find.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <sstream>
using namespace std;

void solution(int n, vector<vector<int>>& connections){
    sort(connections.begin(),connections.end(),[](vector<int>&a, vector<int>&b){
        return a[2]<b[2];
    });

    UF uf(n+1);//好阴险的，他的起始编号是1开始的。
    int res=0;
    for(auto& c:connections){
        int a = c[0];
        int b = c[1];
        int val = c[2];
        if(uf.connected(a,b)){
            continue;
        }
        uf.union_(a,b);
        res += val;
    }

/*
    // 保证所有节点都被连通
    // 按理说 uf.count() == 1 说明所有节点被连通
    // 但因为节点 0 没有被使用，所以 0 会额外占用一个连通分量
    */
    if(uf.get_count()==2) {
        cout<<res<<endl;
        return;
    }
    else cout<<-1<<endl;
    

}

int main(){
    int n;
    cin>>n;
    cin.ignore();

    vector<vector<int>> connections;
    string tmp;
    getline(cin,tmp);
    tmp+= " ";
    for(int i=0;i<tmp.size();i++){
        if(tmp[i]==' '){
            int a=tmp[i-5] -'0';
            int b = tmp[i-3]- '0';
            int c = tmp[i-1]- '0';

            connections.push_back({a,b,c});
        }
    }
    
    solution(n,connections);
}