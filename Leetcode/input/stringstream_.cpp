
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    stringstream ss;
    string ab,count;
    int a,b;
    while(cin>>ab>>count){
        // cout<<":::"<<ab<<" "<<count<<endl;
        int index = count.find(':');
        a = stoi(count.substr(0,index));
        b = stoi(count.substr(index+1));
        cout<<a<<" "<<b<<endl;
        
    }

    return 0;
}