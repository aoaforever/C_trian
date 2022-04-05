/*
给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

// 买+卖为1次交易，只需扣一次手续费
// k为无穷
#include <iostream>
#include <vector>


using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices,int fee) {
        int N = prices.size();
        int dp[N+1][2];

        dp[0][0] = 0;
        dp[0][1] = INT_MIN;

        for(int i=1;i<=N;i++){
            dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
            //如果i是第一天，那么直接由第0天转移过来。
            //如果第1天要买，那么就是直接-当天的价格就好。不需要-1天的理论。
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i-1]-fee);
                            
        }
        return dp[N][0];
    }
};