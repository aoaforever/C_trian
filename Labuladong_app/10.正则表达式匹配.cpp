/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 *
 * https://leetcode-cn.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (31.61%)
 * Likes:    2984
 * Dislikes: 0
 * Total Accepted:    275.9K
 * Total Submissions: 872.6K
 * Testcase Example:  '"aa"\n"a"'
 *
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
 * 
 * 
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 * 
 * 
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "aa", p = "a"
 * 输出：false
 * 解释："a" 无法匹配 "aa" 整个字符串。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入：s = "aa", p = "a*"
 * 输出：true
 * 解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "ab", p = ".*"
 * 输出：true
 * 解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 20
 * 1 <= p.length <= 30
 * s 只包含从 a-z 的小写字母。
 * p 只包含从 a-z 的小写字母，以及字符 . 和 *。
 * 保证每次出现字符 * 时，前面都匹配到有效的字符
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int n,m;
    unordered_map<string,bool> memo;
    bool isMatch(string s, string p) {
        n = s.size(), m = p.size();
        return dp(s,0,p,0);
    }
    bool dp(string& s, int i, string& p, int j){
        if(j==m){
            return i==n;
        }
        if(i==n){
            if((m-j)%2==1) return false;
            for(;j+1<m;j=j+2){
                if(p[j+1]!='*') return false;
            }
            return true;
        }

        string key = to_string(i)+","+to_string(j);
        if(memo.count(key)) return memo[key];
        bool res =false;
        if(s[i]==p[j]||p[j]=='.'){
            if(p[j+1]=='*'){
                res = dp(s,i,p,j+2)||dp(s,i+1,p,j);//匹配0次或者多次
            }
            else res = dp(s,i+1,p,j+1);
        }
        else{
            if(p[j+1]=='*')  res = dp(s,i,p,j+2);//匹配0次
            else res =  false;
        } 
        memo[key] = res;
        return memo[key];
    }
};
// @lc code=end

