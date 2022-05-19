/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 *
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (57.77%)
 * Likes:    2358
 * Dislikes: 0
 * Total Accepted:    792.3K
 * Total Submissions: 1.4M
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
 * 
 * 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
 * 
 * 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：[7,1,5,3,6,4]
 * 输出：5
 * 解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
 * ⁠    注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：prices = [7,6,4,3,1]
 * 输出：0
 * 解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// class Solution {
// public:
// //只能交易一次，因此当我今天要买，就表示之前没买，那么之前的利润肯定为0
//     int maxProfit(vector<int>& prices) {
//         int s=prices.size();
//         vector<vector<int>> dp(s+1,vector<int>(2));
        
//         dp[0][0] = 0;
//         dp[0][1] = INT_MIN;
//         for(int i=1;i<dp.size();i++){
//             dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
//             dp[i][1] = max(dp[i-1][1],-prices[i-1]);
//             // cout<<dp[i][0]<<" "<<dp[i][1]<<endl;
//         }
//         return dp[s][0];

//     }
    
// };
class Solution {
public:
//只能交易一次，因此当我今天要买，就表示之前没买，那么之前的利润肯定为0
    int maxProfit(vector<int>& prices) {
        int s=prices.size();
        // vector<vector<int>> dp(s+1,vector<int>(2));
        vector<int> dp(2);      
        // dp[0][0] = 0;
        // dp[0][1] = INT_MIN;
        dp[0] =0;
        dp[1] = INT_MIN;
        for(int i=1;i<s+1;i++){
            // dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
            // dp[i][1] = max(dp[i-1][1],-prices[i-1]);
            dp[0] = max(dp[0],dp[1]+prices[i-1]);
            dp[1] = max(dp[1],-prices[i-1]);
            // cout<<dp[i][0]<<" "<<dp[i][1]<<endl;
        }
        return dp[0];

    }
    
};

//又发现，dp和i一点关系都没有
class Solution {
public:
//只能交易一次，因此当我今天要买，就表示之前没买，那么之前的利润肯定为0
    int maxProfit(vector<int>& prices) {
        int s=prices.size();

        int dp_0 = 0;
        int dp_1 = INT_MIN;
        for(int i=1;i<s+1;i++){

            dp_0 = max(dp_0,dp_1+prices[i-1]);
            dp_1 = max(dp_1, -prices[i-1]);

        }
        return dp_0;

    }
    
};
// @lc code=end

