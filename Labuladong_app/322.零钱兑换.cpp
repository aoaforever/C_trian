/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 *
 * https://leetcode-cn.com/problems/coin-change/description/
 *
 * algorithms
 * Medium (45.54%)
 * Likes:    1934
 * Dislikes: 0
 * Total Accepted:    440.1K
 * Total Submissions: 965.7K
 * Testcase Example:  '[1,2,5]\n11'
 *
 * 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
 * 
 * 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 * 
 * 你可以认为每种硬币的数量是无限的。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：coins = [1, 2, 5], amount = 11
 * 输出：3 
 * 解释：11 = 5 + 5 + 1
 * 
 * 示例 2：
 * 
 * 
 * 输入：coins = [2], amount = 3
 * 输出：-1
 * 
 * 示例 3：
 * 
 * 
 * 输入：coins = [1], amount = 0
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= coins.length <= 12
 * 1 <= coins[i] <= 2^31 - 1
 * 0 <= amount <= 10^4
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        
        int count =0;
        for(int i=coins.size()-1;i>=0;i--){
            if(amount/coins[i]>0){
                int sum=0;
                count += amount/coins[i];
                sum += amount/coins[i]* coins[i];
                amount -= sum;
                cout<<count<<"   "<<amount<<endl;
            }
        }
        if(amount==0) return count;
        return -1;
    }
};

class Solution {
public:
    vector<int> memo;
    int coinChange(vector<int>& coins, int amount) {
        memo.resize(amount+1,-666);
        sort(coins.begin(),coins.end());
        dp(coins,amount);

        return memo[amount];
    }
    int dp(vector<int>& coins,int amount){
        if(amount<0) return -1;
        if(amount==0) {
            memo[amount]=0;
            return 0;
            }
        if(memo[amount]!= -666) return memo[amount];
        int res=INT_MAX;

        for(auto& c :coins){
            int subproblem = dp(coins,amount-c);
            if(subproblem==-1) continue;//当前硬币太大，跳过，如果一直跳过，则res=INT_MAX
            res = min(res,subproblem+1);
        }
        
        memo[amount] = (res==INT_MAX)?-1:res;
        return memo[amount];
    }
};
// @lc code=end

