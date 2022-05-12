#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string s;
    // while(getline(cin,s)){
    //     cout<<s<<endl;
    // }

    getline(cin,s);
    // cout<<s<<endl;

    stringstream asd;
    asd<<s;
    // cout<<asd.str()<<endl;
    string x;
    while(asd>>x){
        cout<<x<<" ";
    }
    return 0;
}