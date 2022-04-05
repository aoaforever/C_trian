#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int change(int amount, vector<int>& coins) {
        memo = vector<vector<int>>(coins.size()+1,vector<int>(amount+1,-1));
        dp(coins.size(),amount,coins);
        return memo[coins.size()][amount];
        // return dp(coins.size(),amount,coins);
    }

    //dp[i][amount]代表：前i个物品下，能够组合成amount的组合个数。
    // i:1~N，代表前i个物品
    // i-1代表当前硬币
    int dp(int i, int amount,vector<int>& coins){
        if(amount<=0){
            //如果金额<0,那么只有不选硬币这唯一一种做法
            memo[i][amount] = 1;
            return memo[i][amount];
        }
        if(i<1){
            //如果不能选硬币，那么组合数为0；
            return 0;
        }
        if(memo[i][amount]!=-1){
            return memo[i][amount];
        }

        if(amount-coins[i-1]<0){
            //那就是不能那这个硬币组合，超重，超额
            memo[i][amount] = dp(i-1,amount,coins);
            return memo[i][amount];
        }
        else{
            //如果可以拿这个硬币，那么试着用
            memo[i][amount] = dp(i,amount-coins[i-1],coins)+dp(i-1,amount,coins);
            return memo[i][amount];
        }
    }
};