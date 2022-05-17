/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 *
 * https://leetcode-cn.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (77.42%)
 * Likes:    2627
 * Dislikes: 0
 * Total Accepted:    501.4K
 * Total Submissions: 647.5K
 * Testcase Example:  '3'
 *
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 3
 * 输出：["((()))","(()())","(())()","()(())","()()()"]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1
 * 输出：["()"]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 8
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
    vector<string> res;
    string tmp;
    string choice = "()";
    vector<string> generateParenthesis(int n) {
        tmp="";
        backtrack(n,n);
        return res;
    }
    void backtrack(int left,int right){
        if(left>right) return;//如果right用得更多，就出错
        if(left<0||right<0) return;//如果用的超出次数也出错
        if(left==0&&right==0){
            res.push_back(tmp);
            return;
        }
        for(char c:choice){//选左括号或者右括号
            //做选择
            if(c=='('){
                tmp.push_back('(');
                backtrack(left-1,right);
            }
            else {
                tmp.push_back(')');
                backtrack(left,right-1);
            }
            //撤销选择
            tmp.pop_back();
        }
    }
};
// @lc code=end

