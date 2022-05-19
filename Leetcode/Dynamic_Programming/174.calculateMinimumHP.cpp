#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        memo = vector<vector<int>>(dungeon.size(),vector<int>(dungeon[0].size(),-1));
        return dp(dungeon,0,0);
    }

    //dp代表i，j得最少初始生命值
    int dp(vector<vector<int>>&dungeon,int i,int j){
        //base case
        //越界
        if(i>=dungeon.size()||j>=dungeon[0].size()){return INT_MAX;}
        //结束条件
        if(i==dungeon.size()-1 && j==dungeon[0].size()-1){
            //如果当前是负值，因为初始生命值必须>=1, 因此如果要经过这个位置，那么初始生命值就是-dungeon[i][j]+1，
            // 这样经过这个位置之后的生命值就剩1。
            //如果当前位置是正值，那就无所谓，取个最小初始值1.
            return dungeon[i][j]<=0? -dungeon[i][j]+1 : 1; //这里会出错。
        }
        if(memo[i][j]!=-1) return memo[i][j];
        int res;
        //从右和下决定当前的最低初始健康点数
        int right = dp(dungeon,i,j+1);
        int down = dp(dungeon,i+1,j);
        res = min(right,down) - dungeon[i][j] ;
        
        res = res<=0?1:res;
        memo[i][j] = res;
        return memo[i][j];
    }
};



//每次dp完都需要判断是否<=0.
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int r=dungeon.size();
        int c = dungeon[0].size();
        vector<vector<int>> dp(r,vector<int>(c));
        dp[r-1][c-1] = dungeon[r-1][c-1]<=0? 1-dungeon[r-1][c-1]:1;
        for(int i=c-2;i>=0;i--){
            dp[r-1][i] = dp[r-1][i+1] -dungeon[r-1][i];
            if(dp[r-1][i]<=0) dp[r-1][i]=1;
        }
        for(int i=r-2;i>=0;i--){
            for(int j=c-1;j>=0;j--){
                // cout<<i<<" "<<j<<endl;
                if(j==c-1) {
                    dp[i][j] = dp[i+1][j] -dungeon[i][j];
                    if(dp[i][j]<=0) dp[i][j]=1;
                    continue;
                }
                dp[i][j] = min(dp[i+1][j],dp[i][j+1]) - dungeon[i][j];
                if(dp[i][j]<=0) dp[i][j]=1;
            }
        }
        return dp[0][0]>0?dp[0][0]:1;
    }
};

//压缩
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int r=dungeon.size();
        int c = dungeon[0].size();

        vector<int>dp(c);
        dp[c-1] = dungeon[r-1][c-1]<=0? 1-dungeon[r-1][c-1]:1;

        for(int i=c-2;i>=0;i--){
            dp[i] = dp[i+1] -dungeon[r-1][i];
            if(dp[i]<=0) dp[i]=1;
        }
        for(int i=r-2;i>=0;i--){
            dp[c-1] = dp[c-1] - dungeon[i][c-1];
            if(dp[c-1]<=0) dp[c-1]=1;
            for(int j=c-2;j>=0;j--){
                dp[j] = min(dp[j],dp[j+1]) - dungeon[i][j];
                if(dp[j]<=0) dp[j]=1;
            }
        }
        return dp[0]>0?dp[0]:1;
    }
};