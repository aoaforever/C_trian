/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 *
 * https://leetcode-cn.com/problems/sudoku-solver/description/
 *
 * algorithms
 * Hard (67.34%)
 * Likes:    1255
 * Dislikes: 0
 * Total Accepted:    142.5K
 * Total Submissions: 211.3K
 * Testcase Example:  '[["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]'
 *
 * 编写一个程序，通过填充空格来解决数独问题。
 * 
 * 数独的解法需 遵循如下规则：
 * 
 * 
 * 数字 1-9 在每一行只能出现一次。
 * 数字 1-9 在每一列只能出现一次。
 * 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
 * 
 * 
 * 数独部分空格内已填入了数字，空白格用 '.' 表示。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：board =
 * [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
 * 
 * 输出：[["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
 * 解释：输入的数独如上图所示，唯一有效的解决方案如下所示：
 * 
 * 
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * board.length == 9
 * board[i].length == 9
 * board[i][j] 是一位数字或者 '.'
 * 题目数据 保证 输入数独仅有一个解
 * 
 * 
 * 
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
    int row ;
    int col;

    void solveSudoku(vector<vector<char>>& board) {
        row = board.size();
        col = board[0].size();
        backtrack(board,0,0);
    }
    bool backtrack(vector<vector<char>>& board,int r,int c){
        // if(r>=row&&c>=col) return false;
        if(r==row-1&&c==col) return true;
        if(c>=col) return backtrack(board,r+1,0);
        
        cout<<r<<" "<<c<<endl;
        if(board[r][c]!='.'){
            //已经被填了
            return backtrack(board,r,c+1);
        }
        for(char cs='1';cs<='9';cs++){
            //选择列表
            if(isValid(cs,board,r,c)){
                //如果可以填
                //做选择
                board[r][c] = cs;
                if(backtrack(board,r,c+1)){
                    return true;
                }
                //撤销选择
                board[r][c] = '.';
            }
            else{
                //如果不可以填当前数字，那就跳过，下一个数字
                continue;
            }
        }
        return false;//如果选择列表都选完了，还没返回true，那就只能返回false
    }
    bool isValid(char&cs, vector<vector<char>>&board,int r,int c){
        for(int i=0;i<9;i++){
            if(board[r][i]==cs) return false;
            if(board[i][c]==cs) return false;
            if(board[(r/3)*3+i/3][(c/3)*3+i%3]==cs) return false;
             
        }
        return true;
    }
};
// @lc code=end

