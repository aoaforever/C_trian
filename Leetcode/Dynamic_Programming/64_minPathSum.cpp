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