/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 *
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (55.89%)
 * Likes:    1125
 * Dislikes: 0
 * Total Accepted:    180.2K
 * Total Submissions: 321.5K
 * Testcase Example:  '[3,3,5,0,0,3,1,4]'
 *
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
 * 
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入：prices = [3,3,5,0,0,3,1,4]
 * 输出：6
 * 解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
 * 随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：prices = [1,2,3,4,5]
 * 输出：4
 * 解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4
 * 。   
 * 注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。   
 * 因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：prices = [7,6,4,3,1] 
 * 输出：0 
 * 解释：在这个情况下, 没有交易完成, 所以最大利润为 0。
 * 
 * 示例 4：
 * 
 * 
 * 输入：prices = [1]
 * 输出：0
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

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int s=prices.size();
        vector<vector<vector<int>>>dp(s+1,vector<vector<int>>(3,vector<int>(2)));
        int k =2;
        for(int i=0;i<=k;i++){
            dp[0][i][0] = 0;
            dp[0][i][1] = INT_MIN;
        }
        for(int i=0;i<s+1;i++){
            dp[i][0][0] = 0;
            dp[i][0][1] = INT_MIN;
        }
        for(int i=1;i<s+1;i++){
            for(int k=1;k<=2;k++){//遍历顺序怎么确定？
                //dp[i][k] -> dp[i-1][k-1],是上一层就改变的树，不管你k往哪个方向遍历，都取得是上一层的值，而不是当前层
                dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1]+prices[i-1]);
                dp[i][k][1] = max(dp[i-1][k][1],dp[i-1][k-1][0]-prices[i-1]);
            }
        }
        return dp[s][2][0];

    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int s=prices.size();

        vector<vector<int>>dp(3,vector<int>(2));
        int k =2;
        for(int i=0;i<=k;i++){
            dp[i][0] = 0;
            dp[i][1] = INT_MIN;
        }
        for(int i=1;i<s+1;i++){
            
            for(int k=1;k<=2;k++){//遍历顺序怎么确定？
                //dp[i][k] -> dp[i-1][k-1],是上一层就改变的树，不管你k往哪个方向遍历，都取得是上一层的值，而不是当前层
                dp[k][0] = max(dp[k][0],dp[k][1]+prices[i-1]);
                dp[k][1] = max(dp[k][1],dp[k-1][0]-prices[i-1]);//上一层的k-1已经被修改完了，不需要中间变量存储
            }
        }
        return dp[2][0];

    
    }
};

// @lc code=end

