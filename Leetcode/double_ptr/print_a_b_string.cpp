#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void help(string& a, string &b){
    int i=0,j=0;
    while(i<a.size()&&j<b.size()){
        cout<<a[i++]<<b[j++];
    }

    while(i<a.size()){
        cout<<a[i++];
    }
    while(j<b.size()){
        cout<<b[j++];
    }

}

int main(){
    // string a,b;

    // getline(cin,a);
    // getline(cin,b);
    // help(a,b);


    vector<int> asd{1,2,4,5,5,5,5,7,8};
    cout<<asd.size()<<endl;
    auto i = lower_bound(asd.begin(),asd.end(),5);
    auto d = upper_bound(asd.begin(),asd.end(),5);
    cout<<*i<<" "<<*d<<endl;
    cout<<i-asd.begin()<<endl;

    return 0;
}