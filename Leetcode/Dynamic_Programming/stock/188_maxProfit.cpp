#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int len = prices.size();
        int dp[len+1][k+1][2];
        //k:1~2, k-1表示下标
        //base case 
        //第0天，dp[0][...][0] =0
        //      dp[0][...][1] = INT_MIN
        //现在最大交易次数为2 dp[...][0][0] =  0
        //                   dp[...][0][1] = INT_MIN
        
        int K =k;        
        
        for(int i=0;i<=len;i++){
            dp[i][0][0] =0;
            dp[i][0][1] =INT_MIN;
        }
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