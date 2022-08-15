//前缀树
//要实现的api
// 更新前缀树
// 查找
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
class tri_tree{
public:
    char tri[12000][11];
    int count[12000];
    int cnt=0;
    tri_tree(){
        memset(tri,0,sizeof(tri));
        memset(count,0,sizeof(count));
    }
    void insert(string& s){
        //将电话号码插入到百名到钟
        int p = 0;
        for(int i=0;i<s.size();i++){
            int c = s[i]-'0';
            if(s[i]=='*') c = 10;

            if(tri[p][c]==0)  tri[p][c] = ++cnt;
            p = tri[p][c]; 
        }
        
        count[p] =1;
    }

    bool find(string& s){
        int p=0;
        for(int i=0;i<s.size();i++){
            int c = s[i]-'0';
            if(tri[p][10]!=0) return true;
            if(tri[p][c]==0) return false;
            
            p=tri[p][c];
        }
        return count[p]!=0;
    }



};

int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    cin.ignore();
    vector<pair<char,string>> v;
    string tmp;

    tri_tree tri;

    for(int i=0;i<n;i++){
        getline(cin,tmp);
        char op = tmp[0];
        string num = tmp.substr(2);
        v.emplace_back(op,num);
    }
    for(auto& s:v){
        char op = s.first;
        string& num = s.second;
        if(op=='C') {
            cout<<tri.find(num)<<endl;
        }
        else if(op=='W'){
            tri.insert(num);
        }
    }
    return 0;
}
