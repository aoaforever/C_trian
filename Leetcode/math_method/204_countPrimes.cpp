#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
//返回质数数量，质数是只能被1和自己整除。
//小于n，不包括n
    int countPrimes(int n) {
        int res=0;
        for(int i=2;i<n;i++){
            if(isPrimes(i)) res++;
        }
        return res;
    }
    bool isPrimes(int i){
        for(int j=2;j<=sqrt(i);j++){//为什么要是等于号？
        //现在我不需要你遍历所有<i的数，只需要遍历<=sqrt(i)的数就能够得出答案。
            if(i%j==0) return false;
        }
        return true;
    }
};

//要怎么继续优化？？
//反过来思考。2的倍数都不是质数，3的倍数都不是质数。
//当遍历到2 的时候，2*3,2*4...2*k<n 的数都不是质数。
//当遍历到3 的时候，3*4,3*5...3*k<n 的数都不是质数。


class Solution {
public:
//返回质数数量，质数是只能被1和自己整除。
//小于n，不包括n
    int countPrimes(int n) {
        int res=0;
        vector<bool> memo(n,true);
        for(long i=2;i<n;i++){//long 确保乘法不会溢出。
            for(long  j=i*i;j<n;j=j+i)//不知不觉的就已经优化了内部循环。j本来是从2*i开始的。
                memo[j] = false;
        }
        //memo的下标就是该元素，如果是true，那么该元素是素数。
        for(int i=2;i<n;i++){
            if(memo[i]==true) res++;
        }
        return res;
    }
    
};

//由于因子的对称性，可以只检查<=sqrt(n)的数
class Solution {
public:
//返回质数数量，质数是只能被1和自己整除。
//小于n，不包括n
    int countPrimes(int n) {
        int res=0;
        vector<bool> memo(n,true);
        for(long i=2;i<=sqrt(n);i++){//long 确保乘法不会溢出。
            for(long  j=i*i;j<n;j=j+i)//不知不觉的就已经优化了内部循环。j本来是从2*i开始的。
                memo[j] = false;
        }
        //memo的下标就是该元素，如果是true，那么该元素是素数。
        for(int i=2;i<n;i++){
            if(memo[i]==true) res++;
        }
        return res;
    }
    
};