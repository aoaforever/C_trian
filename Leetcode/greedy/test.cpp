#include <iostream>
#include <vector>

using namespace std;

int main(){
    // int* a=new int[10];
    // int* b=new int(10);

    // cout<<sizeof(a)<<","<<sizeof(b)<<endl;
    // cout<<*(a+3)<<","<<*(b+0)<<endl;
    vector<int> a{1,2,3};
    cout<<a[0]<<a[1]<<a[2]<<endl;
    
    return 0;
}