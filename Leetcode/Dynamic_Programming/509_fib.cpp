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