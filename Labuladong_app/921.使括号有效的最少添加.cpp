/*
 * @lc app=leetcode.cn id=921 lang=cpp
 *
 * [921] 使括号有效的最少添加
 *
 * https://leetcode-cn.com/problems/minimum-add-to-make-parentheses-valid/description/
 *
 * algorithms
 * Medium (74.88%)
 * Likes:    131
 * Dislikes: 0
 * Total Accepted:    28.8K
 * Total Submissions: 38.4K
 * Testcase Example:  '"())"'
 *
 * 只有满足下面几点之一，括号字符串才是有效的：
 * 
 * 
 * 它是一个空字符串，或者
 * 它可以被写成 AB （A 与 B 连接）, 其中 A 和 B 都是有效字符串，或者
 * 它可以被写作 (A)，其中 A 是有效字符串。
 * 
 * 
 * 给定一个括号字符串 s ，移动N次，你就可以在字符串的任何位置插入一个括号。
 * 
 * 
 * 例如，如果 s = "()))" ，你可以插入一个开始括号为 "(()))" 或结束括号为 "())))" 。
 * 
 * 
 * 返回 为使结果字符串 s 有效而必须添加的最少括号数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "())"
 * 输出：1
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "((("
 * 输出：3
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 1000
 * s 只包含 '(' 和 ')' 字符。
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
    int minAddToMakeValid(string s) {
        int need=0;
        int res =0;

        for(int i=0;i<s.size();i++){
            char c = s[i];
            if(c=='('){
                need++;//右括号需要多一个
            }
            else{
                need--;//右括号减一个
                if(need==-1){
                    //如果右括号太多了
                    need=0;
                    res++;//左括号加一个
                }
            }
        }
        return res+need;
    }
};
// @lc code=end

