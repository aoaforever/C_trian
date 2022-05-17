#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<int>>memo;
    int minPathSum(vector<vector<int>>& grid) {
        int r=grid.size(), c=grid[0].size();
        memo = vector<vector<int>>(r,vector<int>(c,-1));
        return dp(r-1,c-1,grid);
    }
    //dp代表i,j位置的最小路径和。
    int dp(int i, int j, vector<vector<int>>&grid){
        
        if(i==0&&j==0) {
            memo[i][j] = grid[i][j];
            return memo[i][j];}
        if((i<0&&j>=0) || (i>=0&&j<0)) return INT_MAX;
        
        //当前的最小路径和取决于之前的最小路径和。
        //只能往左上走。
        if(memo[i][j]!=-1) return memo[i][j];
        memo[i][j] = min(dp(i-1,j,grid),dp(i,j-1,grid))+grid[i][j];
        return memo[i][j];


    }
};

class Solution {
public:
    int r,c;
    
    int minPathSum(vector<vector<int>>& grid) {
        r=grid.size(),c=grid[0].size();
        vector<vector<int>> dp(r,vector<int>(c));
        //不需要扩张，原来的大小就可以，但是要确定初始值
        dp[0][0] = grid[0][0];
        for(int i=1;i<r;i++){
            dp[i][0] = dp[i-1][0]+grid[i][0];
        }
        for(int i=1;i<c;i++){
            dp[0][i] = dp[0][i-1] + grid[0][i];
        }
        for(int i=1;i<r;i++){
            for(int j=1;j<c;j++){
                dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[r-1][c-1];
    }

};

//二维压缩成一维
class Solution {
public:
    int r,c;
    
    int minPathSum(vector<vector<int>>& grid) {
        r=grid.size(),c=grid[0].size();
        vector<int> dp(c);
        //不需要扩张，原来的大小就可以，但是要确定初始值
        dp[0] = grid[0][0];
        for(int i=1;i<c;i++){
            dp[i] = dp[i-1] + grid[0][i];
        }
        for(int i=1;i<r;i++){
            dp[0] = dp[0] + grid[i][0];
            for(int j=1;j<c;j++){
                dp[j] = min(dp[j],dp[j-1]) + grid[i][j];
            }
        }
        return dp[c-1];
    }

};