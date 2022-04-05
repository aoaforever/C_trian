#include <iostream>
#include <vector>


using namespace std;
/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

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
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<vector<int>>> dp(len+1,vector<vector<int>>(2,vector<int>(2)));
        //base case 
        //第0天，dp[0][...][0] =0
        //      dp[0][...][1] = INT_MIN
        //最大交易次数为0, dp[...][0][0] = 0
        //                dp[...][0][1] = INT_MIN
        int K=1;
        for(int k=0;k<=1;k++){
            dp[0][k][0]=0;
            dp[0][k][1]=INT_MIN;
        }
        for(int i=0;i<=len;i++){
            dp[i][0][0] = 0;
            dp[i][0][1]=INT_MIN;
        }

        for(int i=1;i<=len;i++){
            for(int k=K;k>=1;k--){
                //今天不会持有有两种情况，一是卖了，二是一直没持有
                dp[i][k][0] = max(dp[i-1][k][1]+prices[i-1],dp[i-1][k][0]);
                //今天持有有两种情况，一是买了，二是一直持有
                dp[i][k][1] = max(dp[i-1][k-1][0]-prices[i-1],dp[i-1][k][1]);
            }
        }
        return dp[len][1][0];
    }
};

//仔细观察发现，K为1，dp[i-1][k-1][0]=dp[i-1][0][0]=dp[...][0][0] = 0
//那么整个dp与k无关，因此可以压缩。
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
        
        
        dp[0][0]=0;
        dp[0][1]=INT_MIN;

        for(int i=1;i<=len;i++){
            
            //今天不会持有有两种情况，一是卖了，二是一直没持有
            dp[i][0] = max(dp[i-1][1]+prices[i-1],dp[i-1][0]);
            //今天持有有两种情况，一是买了，二是一直持有
            dp[i][1] = max(-prices[i-1],dp[i-1][1]);
        
        }
        return dp[len][0];
    }
};

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


int main(){
    Solution a;
    vector<int> b({1,2,3,4,5});
    int c =2;
    vector<vector<vector<int>>> dp(6,vector<vector<int>>(2,vector<int>(2)));
  
    return 0;
}