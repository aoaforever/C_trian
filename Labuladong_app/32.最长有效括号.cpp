/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 *
 * https://leetcode-cn.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (36.33%)
 * Likes:    1790
 * Dislikes: 0
 * Total Accepted:    259.8K
 * Total Submissions: 715K
 * Testcase Example:  '"(()"'
 *
 * 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "(()"
 * 输出：2
 * 解释：最长有效括号子串是 "()"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = ")()())"
 * 输出：4
 * 解释：最长有效括号子串是 "()()"
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = ""
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * s[i] 为 '(' 或 ')'
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
#include <stack>
using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.size()+1,0);
        stack<int> stk;
        for(int i=0;i<s.size();i++){
            char c = s[i];
            if(c=='('){
                stk.push(i);
                dp[i+1] =0;
            }
            else{
                if(!stk.empty()){
                    int leftindex= stk.top();
                    stk.pop();
                    int len = i-leftindex+1 + dp[leftindex];
                    dp[i+1] = len;//记得更新结果啊
                }
                else{
                    //如果是空栈
                    dp[i+1] =0;//则当前元素的最长长度为0
                }
            }
        }
        int res=0;
        for(int i=0;i<dp.size();i++){
            res = max(res,dp[i]);
        }
        return res;
    }
};
// @lc code=end

