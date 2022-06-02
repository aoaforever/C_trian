/*
给定从 0 到 n-1 标号的 n 个结点，和一个无向边列表（每条边以结点对来表示），
请编写一个函数用来判断这些边是否能够形成一个合法有效的树结构。


示例 1：
 
输入: n = 5, 边列表 edges = [[0,1], [0,2], [0,3], [1,4]]
输出: true
 
示例 2:
 
输入: n = 5, 边列表 edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
输出: false
 
注意：你可以假定边列表 edges 中不会出现重复的边。由于所有的边是无向边，边 [0,1] 和边 [1,0] 是相同的，因此不会同时出现在边列表 edges 中。

*/

#include "Union_find.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <sstream>
using namespace std;


void solution(int n, vector<vector<int>>& edges){
    UF uf(n);
    for(auto & e:edges){
        int a=e[0];
        int b = e[1];
        if(uf.connected(a,b)){
            cout<<"false"<<endl;
            return ;
        }
        uf.union_(a,b);
    }
    if(uf.get_count()==1) cout<<"true"<<endl;

    else cout<<"false"<<endl;

}

int main(){
    int n;
    cin>>n;

    vector<vector<int>> edges;
    // for(int i=0;i<n;i++){
    //     int a,b;
    //     cin>>a>>b;
    //     edges.emplace_back(vector<int>{a,b});
    // }
    cin.ignore();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    string tmp;
    getline(cin,tmp);
    cout<<tmp<<endl;
    for(int i=0;i<tmp.size();i++){
        if(tmp[i]==','){
            int a,b;
            a=tmp[i-1]-'0';
            b = tmp[i+1]-'0';
            edges.push_back({a,b});
        }
    }
    solution(n,edges);

    return 0;
}