/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 *
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (41.30%)
 * Likes:    729
 * Dislikes: 0
 * Total Accepted:    126.3K
 * Total Submissions: 304.6K
 * Testcase Example:  '2\n[2,4,1]'
 *
 * 给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。
 * 
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
 * 
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：k = 2, prices = [2,4,1]
 * 输出：2
 * 解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：k = 2, prices = [3,2,6,5,0,3]
 * 输出：7
 * 解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
 * ⁠    随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 =
 * 3 。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * 0 
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
    int maxProfit(int k, vector<int>& prices) {
        int s=prices.size();

        vector<vector<int>>dp(k+1,vector<int>(2));
        // int k =2;
        for(int i=0;i<=k;i++){
            dp[i][0] = 0;
            dp[i][1] = INT_MIN;
        }
        for(int i=1;i<s+1;i++){
            
            for(int j=1;j<=k;j++){//遍历顺序怎么确定？
                //dp[i][k] -> dp[i-1][k-1],是上一层就改变的树，不管你k往哪个方向遍历，都取得是上一层的值，而不是当前层
                dp[j][0] = max(dp[j][0],dp[j][1]+prices[i-1]);
                dp[j][1] = max(dp[j][1],dp[j-1][0]-prices[i-1]);//上一层的k-1已经被修改完了，不需要中间变量存储
            }
        }
        return dp[k][0];

    }
};
// @lc code=end

