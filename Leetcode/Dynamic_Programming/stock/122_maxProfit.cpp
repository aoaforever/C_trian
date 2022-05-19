#include <iostream>
#include <vector>


using namespace std;
/*
给定一个数组 prices ，其中 prices[i] 表示股票第 i 天的价格。

在每一天，你可能会决定购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以购买它，然后在 同一天 出售。
返回 你能获得的 最大 利润 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

//在这些天内可以多次购买和卖，但是必须买之前必须是未持有。只能有1股。


//买入的时候可交易次数+1.对应到今天与昨天，如果今天的交易次数为k，那么如果今天买入，那么昨天的交易次数必须为k-1.
//状态： i:第i天，i:1~N
//      k:可交易次数,k:1~无穷
//       持有状态：0未持有，1持有

//选择： 今天买、今天不买
// dp[i][k][0]: 第i天,现在没持有股票，最多可交易次数为k，值为这一天的利润
//最终答案： dp[prices.size()][1][0]
//这⾥着重提醒⼀下，时刻牢记「状态」的定义，k 的定义并不是「已进⾏的交易次数」，⽽是「最⼤
//交易次数的上限限制」。如果确定今天进⾏⼀次交易，且要保证截⾄今天最⼤交易次数上限为 k，那
//么昨天的最⼤交易次数上限必须是 k - 1。

//仔细观察发现，K为1，dp[i-1][k-1][0]=dp[i-1][0][0]=dp[...][0][0] = 0
//那么整个dp与k无关，因此可以压缩。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int dp[len+1][2];
        
        //base case 
        //第0天，dp[0][0] =0
        //      dp[0][1] = INT_MIN
        //现在最大交易次数为无穷
        //                
        
        
        dp[0][0]=0;
        dp[0][1]=INT_MIN;

        for(int i=1;i<=len;i++){
            
            //今天不会持有有两种情况，一是卖了，二是一直没持有
            dp[i][0] = max(dp[i-1][1]+prices[i-1],dp[i-1][0]);
            //今天持有有两种情况，一是买了，二是一直持有
            dp[i][1] = max(dp[i-1][0]-prices[i-1],dp[i-1][1]);
        
        }
        return dp[len][0];
    }
};

//下面这个是错的，压缩失败
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len+1,vector<int>(2));
        //base case 
        //第0天，dp[0][0] =0
        //      dp[0][1] = INT_MIN
        //最大交易次数为0, dp[...][0] = 0
        //                dp[...][1] = INT_MIN
        
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for(int i=1;i<=len;i++){
            
            //今天不会持有有两种情况，一是卖了，二是一直没持有
            dp_i_0 = max(dp_i_1+prices[i-1],dp_i_0);
            //今天持有有两种情况，一是买了，二是一直持有
            dp_i_1 = max(-prices[i-1],dp_i_1);
        
        }
        return dp_i_0;
    }
};

//这个才是对的，不过还可以再压缩成3个变量
class Solution {
public:

    int maxProfit(vector<int>& prices) {
        int s = prices.size();
        vector<int>dp(2);
        dp[0] = 0;
        dp[1] = INT_MIN;
        for(int i=1;i<s+1;i++){
            int tmp = dp[0];
            dp[0] = max(dp[0],dp[1]+prices[i-1]);
            dp[1] = max(dp[1],tmp-prices[i-1]);//表示无限交易次数
        }
        return dp[0];

    }
};


int main(){
    Solution a;
    vector<int> b({1,2,3,4,5});
    int c =2;
    vector<vector<vector<int>>> dp(6,vector<vector<int>>(2,vector<int>(2)));
  
    return 0;
}