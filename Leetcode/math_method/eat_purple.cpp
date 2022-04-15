//https://www.nowcoder.com/questionTerminal/14c0359fb77a48319f0122ec175c9ada?answerType=1&f=discussion


#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long eat(long a,long b,long c){
    long sum = a+b+c;
    if(a+b>c) {
        //构成三角形,则没人平分周长
        return (sum+2/3);//需要向上取整，因为求的是吃最多的人情况下吃最少的东西。
    }
    if(2*(a+b)<c){//甲只能吃a,b，吃完就不能吃了。因此乙丙平分c
        return (c+1/2);
    }
    //a+b<c 且 2(a+b)>c
    return (sum+2)/3;//依然能够平分成3段。

}

int main(){
    int T;//组数
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        int num[3]={a,b,c};
        sort(num,num+3);
        cout<<eat(num[0],num[1],num[2]);
    }
    return 0;
}