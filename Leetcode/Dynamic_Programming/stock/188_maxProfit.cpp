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