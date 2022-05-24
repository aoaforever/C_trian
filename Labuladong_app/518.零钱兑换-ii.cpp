/*
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 *
 * https://leetcode-cn.com/problems/coin-change-2/description/
 *
 * algorithms
 * Medium (68.19%)
 * Likes:    822
 * Dislikes: 0
 * Total Accepted:    162.4K
 * Total Submissions: 237.3K
 * Testcase Example:  '5\n[1,2,5]'
 *
 * 给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
 * 
 * 请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
 * 
 * 假设每一种面额的硬币有无限个。 
 * 
 * 题目数据保证结果符合 32 位带符号整数。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：amount = 5, coins = [1, 2, 5]
 * 输出：4
 * 解释：有四种方式可以凑成总金额：
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：amount = 3, coins = [2]
 * 输出：0
 * 解释：只用面额 2 的硬币不能凑成总金额 3 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：amount = 10, coins = [10] 
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * coins 中的所有值 互不相同
 * 0 
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
    vector<vector<int>> memo;
    int change(int amount, vector<int>& coins) {
        memo = vector<vector<int>>(coins.size()+1,vector<int>(amount+1,-666));
        return dp(coins.size(),amount,coins);
    }
    int dp(int i,int amount,vector<int>& coins ){
        if(i<=0) return 0;//没有硬币，怎么都凑不出
        if(amount==0) return 1;//凑出0 ，那就是不凑就有
        if(amount<0) return 0;//这次的硬币太大，你忍一下
        if(memo[i][amount]!=-666) return memo[i][amount];
        int res=0;
        int sub1 = dp(i,amount-coins[i-1],coins);//当前硬币我要用
        int sub2 = dp(i-1,amount,coins);
        res  = sub1+sub2;
        memo[i][amount] = res;
        return res;
    }
};
// @lc code=end

