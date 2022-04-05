#include <iostream>
#include <vector>


using namespace std;
/*
给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

//k是无穷，但是多了冷冻期。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        int dp[N+1][2];

        dp[0][0] = 0;
        dp[0][1] = INT_MIN;

        for(int i=1;i<=N;i++){
            dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
            //如果i是第一天，那么直接由第0天转移过来。
            //如果第1天要买，那么就是直接-当天的价格就好。不需要-1天的理论。
            dp[i][1] = i==1?max(dp[i-1][1],dp[i-1][0]-prices[i-1])
                            :max(dp[i-1][1],dp[i-2][0]-prices[i-1]);
        }
        return dp[N][0];
    }
};