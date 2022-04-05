#include <iostream>
#include <vector>


using namespace std;
/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

//在这些天内只能进行两次交易，但是必须买之前必须是未持有。只能有1股。


//买入的时候可交易次数+1.对应到今天与昨天，如果今天的交易次数为k，那么如果今天买入，那么昨天的交易次数必须为k-1.
//状态： i:第i天，i:1~N
//      k:可交易次数,k:1~2
//       持有状态：0未持有，1持有

//选择： 今天买、今天不买
// dp[i][k][0]: 第i天,现在没持有股票，最多可交易次数为k，值为这一天的利润
//最终答案： dp[prices.size()][2][0]
//这⾥着重提醒⼀下，时刻牢记「状态」的定义，k 的定义并不是「已进⾏的交易次数」，⽽是「最⼤
//交易次数的上限限制」。如果确定今天进⾏⼀次交易，且要保证截⾄今天最⼤交易次数上限为 k，那
//么昨天的最⼤交易次数上限必须是 k - 1。


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int dp[len+1][3][2];
        //k:1~2, k-1表示下标
        //base case 
        //第0天，dp[0][...][0] =0
        //      dp[0][...][1] = INT_MIN
        //现在最大交易次数为2 dp[...][0][0] =  0
        //                   dp[...][0][1] = INT_MIN
        
        int K =2;        
        
        // for(int i=0;i<=len;i++){
        //     dp[i][0][0] =0;
        //     dp[i][0][1] =INT_MIN;
        // }
        for(int k=0;k<=K;k++){
            dp[0][k][0] = 0;
            dp[0][k][1] = INT_MIN;
        }


        for(int i=1;i<=len;i++){
            for(int k=K;k>=1;k--){
           
                //今天不会持有有两种情况，一是卖了，二是一直没持有
                dp[i][k][0] = max(dp[i-1][k][1]+prices[i-1],dp[i-1][k][0]);
                //今天持有有两种情况，一是买了，二是一直持有
                dp[i][k][1] = max(dp[i-1][k-1][0]-prices[i-1],dp[i-1][k][1]);
            }
        }
        return dp[len][K][0];
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