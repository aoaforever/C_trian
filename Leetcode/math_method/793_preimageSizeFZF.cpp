#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    //有几个x满足x!后面有k个0.
    //k最大值10e9,什么x!的尾部能够有10e9个0？
    //INT_MAX！后面有 536870902个0
    //              1000000000
    //LONG_MAX！后面有2305843009213693937个0.足以满足右界。
    int preimageSizeFZF(int k) {
        int res =0;
        
        for(long i=0;i<LONG_MAX;i++){
            long kkk = trailingZeroes(i);
            if(kkk==k) res++;
            else if(kkk<k) continue;
            else break;//因为后面的i!的零数一定会大于k
        }    
        // cout<<trailingZeroes(LONG_MAX);
        return res;
    }
    long trailingZeroes(long n) {
        long res=0;
        for(long i=n;i>0;i/=5){
            res+= i/5;
        }
        return res;
    }
};

//可以发现，trailingZeroes()是一个单调递增函数，可以有平坦区。
//因此可以用二分来进行优化。

class Solution {
public:
    //有几个x满足x!后面有k个0.
    //k最大值10e9,什么x!的尾部能够有10e9个0？
    //INT_MAX！后面有 536870902个0
    //              1000000000
    //LONG_MAX！后面有2305843009213693937个0.足以满足右界。
    int preimageSizeFZF(int k) {
        int res =0;
        long left = left_bound(k);
        long right = right_bound(k);
        res= right-left+1;//由于返回的是下标，而答案要个数，因此需要+1.
        return res;
    }

    long left_bound(int k){
        long left =0, right = LONG_MAX;//[left,right)，左闭右开，结束条件left=right
        while(left<right){
            long mid = left+ (right-left)/2;
            long kkk = trailingZeroes(mid);
            if(kkk<k){
                //往右缩
                left = mid+1;
            }
            else if(kkk>k){
                //往左缩
                right = mid;
            }
            else {
                //往左缩找左边界。
                right = mid;
            }
        }
        return left;
    }
    long right_bound(int k){
        long left =0, right = LONG_MAX;//[left,right)，左闭右开，结束条件left=right
        while(left<right){
            long mid = left+ (right-left)/2;
            long kkk = trailingZeroes(mid);
            if(kkk<k){
                //往右缩
                left = mid+1;
            }
            else if(kkk>k){
                //往左缩
                right = mid;
            }
            else {
                //往右缩找右边界。
                left = mid+1;
            }
        }
        return left-1;//别忘了是左闭右开。所以-1
    }

    long trailingZeroes(long n) {
        long res=0;
        for(long i=n;i>0;i/=5){
            res+= i/5;
        }
        return res;
    }
};