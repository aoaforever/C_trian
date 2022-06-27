#include <bits/stdc++.h>
using namespace std;

bool my_judge(string& s){
    
    if(s[0]!='A'&&s[0]!='S'&&s[0]!='W'&&s[0]!='D') return false;
    if(s[1]<'0'||s[1]>'9') return false;
    if(s.size()>2&&s.size()<4){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(s[2]<'0'||s[2]>'9') return false;    
    }
    return true;
}
void run(string& s){
    int x=0,y=0;
    int m=s.size();
    int i=0,j=0;
    vector<string> vec;
    
    int sublen=0;
    for(int i=0;i<s.size();i++){
        if(s[i]!=';'){
            sublen++;
            continue;
        }
        vec.emplace_back(s.substr(i-sublen,sublen));
        sublen =0;
    }
    
    for(string& v:vec){
        if(my_judge(v)==false) continue;
        int val = stoi(v.substr(1));
        char dir = v[0];
        switch(dir){
            case 'A': x=x-val; break;
            case 'S': y=y-val; break;
            case 'W': y=y+val; break;
            case 'D': x=x+val; break;
        }
        
    }
    cout<<x<<","<<y<<endl;
    
}

int main(){
    string input;
    getline(cin,input);
    
    
    run(input);
    return 0;
}
