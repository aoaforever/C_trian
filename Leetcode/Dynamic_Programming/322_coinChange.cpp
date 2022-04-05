#include <vector>
#include <limits.h>
using namespace std;

class Solution {
public:
    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount+1,0);
        return dp(coins,amount,memo);
    }
    //凑成总金额所需的 最少的硬币个数
    //dp代表amout金额需要的硬币个数。
    //没有使用备忘录肯定会超时的
    int dp(vector<int>&coins,int amount, vector<int>& memo){
        if(amount==0) return 0;
        if(amount<0) return -1;
        int res=INT_MAX;
        for(auto &c:coins){
            //做出了c的选择。那么amount肯定是-c;
            int subproblem =dp(coins,amount-c,memo);
            if(subproblem==-1) continue;//说明此次选择是无效的，不应该算进res;

            res = min(res,1+subproblem); //1代表本层的一次，剩下的交给下一次递归。
        }
        return res==INT_MAX?-1:res; 
    }



};


class Solution {
public:
    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount+1,-2);
        return dp(coins,amount,memo);
    }
    //凑成总金额所需的 最少的硬币个数
    //dp代表amout金额需要的硬币个数。
    //没有使用备忘录肯定会超时的
    int dp(vector<int>&coins,int amount, vector<int>& memo){
        if(amount==0) return 0;
        if(amount<0) return -1;
        int res=INT_MAX;
        for(auto &c:coins){
            //做出了c的选择。那么amount肯定是-c;
            int subproblem;
            if(memo[amount-c] != -2)  subproblem= memo[amount-c];
            else subproblem =dp(coins,amount-c,memo);
            if(subproblem==-1) continue;//说明此次选择是无效的，不应该算进res;

            res = min(res,1+subproblem); //1代表本层的一次，剩下的交给下一次递归。
        }
        memo[amount] = res;
        return res==INT_MAX?-1:memo[amount]; 
    }



};


class Solution {
public:
    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount+1,-2);
        return dp(coins,amount,memo);
    }
    //凑成总金额所需的 最少的硬币个数
    //dp代表amout金额需要的硬币个数。
    //没有使用备忘录肯定会超时的
    int dp(vector<int>&coins,int amount, vector<int>& memo){
        if(amount==0) return 0;
        if(amount<0) return -1;
        //更狠一点，如果amount计算过了，就直接返回amount对应的次数
        if(memo[amount]!=-2) {
            return memo[amount];
        }
        
        int res=INT_MAX;

        for(auto &c:coins){
            //做出了c的选择。那么amount肯定是-c;
            int subproblem;
            subproblem =dp(coins,amount-c,memo);
            if(subproblem==-1) continue;//说明此次选择是无效的，不应该算进res;

            res = min(res,1+subproblem); //1代表本层的一次，剩下的交给下一次递归。
        }
        memo[amount] = res==INT_MAX?-1:res;
        return memo[amount]; 
    }



};