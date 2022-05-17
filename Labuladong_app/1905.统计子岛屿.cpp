/*
 * @lc app=leetcode.cn id=1905 lang=cpp
 *
 * [1905] 统计子岛屿
 *
 * https://leetcode-cn.com/problems/count-sub-islands/description/
 *
 * algorithms
 * Medium (64.09%)
 * Likes:    53
 * Dislikes: 0
 * Total Accepted:    12.9K
 * Total Submissions: 19.9K
 * Testcase Example:  '[[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]]\n' +
  '[[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]'
 *
 * 给你两个 m x n 的二进制矩阵 grid1 和 grid2 ，它们只包含 0 （表示水域）和 1 （表示陆地）。一个 岛屿 是由 四个方向
 * （水平或者竖直）上相邻的 1 组成的区域。任何矩阵以外的区域都视为水域。
 * 
 * 如果 grid2 的一个岛屿，被 grid1 的一个岛屿 完全 包含，也就是说 grid2 中该岛屿的每一个格子都被 grid1
 * 中同一个岛屿完全包含，那么我们称 grid2 中的这个岛屿为 子岛屿 。
 * 
 * 请你返回 grid2 中 子岛屿 的 数目 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]],
 * grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
 * 输出：3
 * 解释：如上图所示，左边为 grid1 ，右边为 grid2 。
 * grid2 中标红的 1 区域是子岛屿，总共有 3 个子岛屿。
 * 
 * 
 * 示例 2：
 * 
 * 输入：grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]],
 * grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
 * 输出：2 
 * 解释：如上图所示，左边为 grid1 ，右边为 grid2 。
 * grid2 中标红的 1 区域是子岛屿，总共有 2 个子岛屿。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * m == grid1.length == grid2.length
 * n == grid1[i].length == grid2[i].length
 * 1 <= m, n <= 500
 * grid1[i][j] 和 grid2[i][j] 都要么是 0 要么是 1 。
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int r;
    int c;
    void dfs(vector<vector<int>>& grid,int i, int j){
        if(i<0||j<0||i>=r||j>=c){
            return;
        }
        if(grid[i][j]==0){
            return;
        }
        grid[i][j] =0;
        dfs(grid,i+1,j);
        dfs(grid,i,j+1);
        dfs(grid,i-1,j);
        dfs(grid,i,j-1);
    }
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        r = grid1.size();
        c=grid1[0].size();
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(grid1[i][j]==0&&grid2[i][j]==1){
                    dfs(grid2,i,j);
                }
            }
        }
        int res=0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(grid1[i][j]==1&&grid2[i][j]==1){
                    res++;
                    dfs(grid2,i,j);
                }
            }
        }
        return res;
    }
    
};
// @lc code=end

