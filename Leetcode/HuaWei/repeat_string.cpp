#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
using namespace std;
//https://blog.csdn.net/m0_61561403/article/details/123240014 第一题
int main(int argc, char const *argv[])
{
    
    unordered_map<string,int> m;

    string t;
    getline(cin,t);


    // cin.ignore();
    // cin.clear();
    int n;
    cin>>n;
    stringstream ii;
    ii<<t;
    string tmp;
    while(ii>>tmp){
        m[tmp]++;
    }
    string res;
    for(auto& i:m){
        if(i.second==n){
            res = i.first;
        }
    }
    cout<<res<<endl;


    
}

