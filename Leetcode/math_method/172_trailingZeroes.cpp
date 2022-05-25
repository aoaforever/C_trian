#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    //找有多少个5因子
    //比如5有一个5因子
    //10有一个5因子
    //25有2个5因子。
    //125有3个5因子。。。
    //答案就是有多少个5因子就有多少个0.
    int trailingZeroes(int n) {
        int res=0;
        for(int i=5;i<=n;i = i*5){
            res += n/i;
        }
        for(int i=n;i>0;i/=5){//这种可以避免整数溢出问题
            res += i/5;
        }
        return res;
    }
};


class Solution {
public:
    int trailingZeroes(int n) {
        int res=0;
        for(;n>0;n=n/5){
            res += n/5;

        }
        return res;
    }
};