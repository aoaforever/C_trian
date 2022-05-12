/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 *
 * https://leetcode-cn.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (73.98%)
 * Likes:    1326
 * Dislikes: 0
 * Total Accepted:    213.3K
 * Total Submissions: 288.1K
 * Testcase Example:  '4'
 *
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 
 * 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
 * 
 * 
 * 
 * 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 4
 * 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * 解释：如上图所示，4 皇后问题存在两个不同的解法。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1
 * 输出：[["Q"]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 9
 * 
 * 
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n) {
        vector<string> path(n,string(n,'.'));
        backtrack(0,n,path);
        return res;
    }
    void backtrack(int row,int n, vector<string>& path){
        if(row==n){
            res.push_back(path);
            return;
        }

        for(int i=0;i<n;i++){
            if(!isValid(row,i,path)){
                continue;
            }
            //如果可以再这个位置下棋
            path[row][i] = 'Q';
            backtrack(row+1,n,path);
            path[row][i] = '.';
        }
    }
    bool isValid(int r,int c, vector<string>& path){
        //只需要监测上方是否有下棋
        //这一列不能有，这一行不能有，左上右上不能有
        for(int i=0;i<path.size();i++){
            if(path[i][c]=='Q') return false;
        }
        //左上角
        for(int i=r-1,j=c-1;i>=0&&j>=0;i--,j--){
            if(path[i][j]=='Q') return false;
        }
        //右上角
        for(int i=r-1,j=c+1;i>=0&&j<path.size();i--,j++){
            if(path[i][j]=='Q') return false;
        }
        return true;
    }
};
// @lc code=end

