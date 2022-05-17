/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
 *
 * https://leetcode-cn.com/problems/minimum-path-sum/description/
 *
 * algorithms
 * Medium (69.18%)
 * Likes:    1251
 * Dislikes: 0
 * Total Accepted:    364.8K
 * Total Submissions: 527.2K
 * Testcase Example:  '[[1,3,1],[1,5,1],[4,2,1]]'
 *
 * 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 
 * 说明：每次只能向下或者向右移动一步。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
 * 输出：7
 * 解释：因为路径 1→3→1→1→1 的总和最小。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：grid = [[1,2,3],[4,5,6]]
 * 输出：12
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 
 * 0 
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// class Solution {
// public:
//     int r,c;
//     vector<vector<int>> memo;
//     int minPathSum(vector<vector<int>>& grid) {
//         r=grid.size(),c=grid[0].size();
//         memo = vector<vector<int>>(r,vector<int>(c,-1));
//         return dp(grid,r-1,c-1);
//     }
//     int dp(vector<vector<int>>&grid, int i, int j){
//         if(i<0||j<0) return INT_MAX;//越界该返回什么？
//         if(i==0&&j==0) return grid[i][j];
//         if(memo[i][j]!=-1) return memo[i][j];
//         int res=INT_MAX;
//         res = min(dp(grid,i-1,j),dp(grid,i,j-1))+grid[i][j];
//         memo[i][j] = res;
//         return res;
//     }
// };

// class Solution {
// public:
//     int r,c;
    
//     int minPathSum(vector<vector<int>>& grid) {
//         r=grid.size(),c=grid[0].size();
//         vector<vector<int>> dp(r,vector<int>(c));
//         //不需要扩张，原来的大小就可以，但是要确定初始值
//         dp[0][0] = grid[0][0];
//         for(int i=1;i<r;i++){
//             dp[i][0] = dp[i-1][0]+grid[i][0];
//         }
//         for(int i=1;i<c;i++){
//             dp[0][i] = dp[0][i-1] + grid[0][i];
//         }
//         for(int i=1;i<r;i++){
//             for(int j=1;j<c;j++){
//                 dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
//             }
//         }
//         return dp[r-1][c-1];
//     }

// };

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
// @lc code=end

