#include <vector>

using namespace std;


//求第n项的斐波那契数

//特点：f(n) = f(n-1) + f(n-2)

//这种解法，自己画一个递归树就知道会有很多重复的节点。因此选择备忘录优化。
class Solution {
public:
    int fib(int n) {
        return dp(n);
    }
    
    int dp(int n){
        if(n==1||n==0) return n;
        return dp(n-1)+ dp(n-2);
    }

    
};

class Solution {
public:
    int fib(int n) {
        //备忘录应该是一组数组，包括下标0~n，总长n+1.
        vector<int> memo(n+1,0);
        return dp(n,memo);
    }
    
    int dp(int n,vector<int>& memo){
        if(n==1||n==0) return n;
        
        if(memo[n]!=0) return memo[n];

        memo[n] = dp(n-1,memo)+ dp(n-2,memo);
        return memo[n] ;
    }

    
};


/*
斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1

*/
//人家连转移方程都给你写好了，还不会写动态规划？？？？？？？
class Solution {
public:
    int fib(int n) {
        if(n<2) return n;
        int fn;
        int fn_1=1,fn_2 =0;
        for(int i=2;i<=n;i++){
            fn = fn_1 + fn_2;
            fn_2 = fn_1;
            fn_1 = fn;
        }
        return fn;
    }
};