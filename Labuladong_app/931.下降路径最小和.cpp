/*
 * @lc app=leetcode.cn id=931 lang=cpp
 *
 * [931] 下降路径最小和
 *
 * https://leetcode-cn.com/problems/minimum-falling-path-sum/description/
 *
 * algorithms
 * Medium (67.09%)
 * Likes:    173
 * Dislikes: 0
 * Total Accepted:    39K
 * Total Submissions: 58.2K
 * Testcase Example:  '[[2,1,3],[6,5,4],[7,8,9]]'
 *
 * 给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。
 * 
 * 下降路径
 * 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。具体来说，位置
 * (row, col) 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1)
 * 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：matrix = [[2,1,3],[6,5,4],[7,8,9]]
 * 输出：13
 * 解释：如图所示，为和最小的两条下降路径
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：matrix = [[-19,57],[-40,-5]]
 * 输出：-59
 * 解释：如图所示，为和最小的下降路径
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == matrix.length == matrix[i].length
 * 1 <= n <= 100
 * -100 <= matrix[i][j] <= 100
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int r,c;
    vector<vector<int>> memo;
    int minFallingPathSum(vector<vector<int>>& matrix) {
        r = matrix.size(), c = matrix[0].size();
        memo = vector<vector<int>>(r,vector<int>(c,-1));

        int res = INT_MAX;
        for(int i=0;i<c;i++){
            res =min(
                dp(matrix,0,i),res);
        }
        return res;
    }
    int dp(vector<vector<int>>& matrix, int row, int col){
        if(col<0||col>=c||row>=r){
            return INT_MAX;
        }
        if(row==r-1){
            return matrix[row][col];
        }
        if(memo[row][col]!=-1) return memo[row][col];

        int res= INT_MAX;
        int subprolem = min(min(dp(matrix,row+1,col+1),dp(matrix,row+1,col)), dp(matrix,row+1,col-1));
        res = matrix[row][col]+subprolem;
        memo[row][col] = res;
        return res;

    }
};
// @lc code=end

