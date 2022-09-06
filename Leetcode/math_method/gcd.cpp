//求 a,和b的最大公因数gcd

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long gcd(long a,long b ){
    // if(a<b) return gcd(b,a);
    // if(b==0) return a;
    if(a%b==0) return b;
    return gcd(b,a%b);
}

int main(){
    long a,b;
    // cin>>a>>b;
    cout<<gcd(98,63);
    return 0;
}