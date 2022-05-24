/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 *
 * https://leetcode-cn.com/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (51.80%)
 * Likes:    773
 * Dislikes: 0
 * Total Accepted:    88.9K
 * Total Submissions: 171.1K
 * Testcase Example:  '"rabbbit"\n"rabbit"'
 *
 * 给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。
 * 
 * 字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE"
 * 的一个子序列，而 "AEC" 不是）
 * 
 * 题目数据保证答案符合 32 位带符号整数范围。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "rabbbit", t = "rabbit"
 * 输出：3
 * 解释：
 * 如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
 * rabbbit
 * rabbbit
 * rabbbit
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "babgbag", t = "bag"
 * 输出：5
 * 解释：
 * 如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。 
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * s 和 t 由英文字母组成
 * 
 * 
 */

// @lc code=start
//组合问题，找长度为t.size(),的内容等于t的子集

//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    
    vector<vector<int>> memo;
    int numDistinct(string s, string t) {
        int n=s.size(),m=t.size();
        memo = vector<vector<int>>(n,vector<int>(m,-1));
        return dp(s,0,t,0);
    }
    int dp(string& s,int i, string& t,int j){
        if(j==t.size()) return 1;
        //那么就要确保每次递归都是选择了正确的字母
        if(s.size()-i < t.size()-j ) return 0;

        if(memo[i][j]!=-1) return memo[i][j];
        int res =0;
        for(int index = i;index<s.size();index++){
            if(s[index]==t[j]){
                int subproblem = dp(s,index+1,t,j+1);
                res += subproblem;
            }
        }
        memo[i][j]=res;
        return memo[i][j];
    }
    // 递归函数本身时间复杂度O(n), 状态个数O(n*m),总时间复杂度O(n*n*m)=O(m*n^2)
};

class Solution {
public:
    
    vector<vector<int>> memo;
    int numDistinct(string s, string t) {
        int n=s.size(),m=t.size();
        memo = vector<vector<int>>(n,vector<int>(m,-1));
        return dp(s,0,t,0);
    }
    int dp(string& s,int i, string& t,int j){
        if(j==t.size()) return 1;
        //那么就要确保每次递归都是选择了正确的字母
        if(s.size()-i < t.size()-j ) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int res= 0;
        if(s[i]==t[j]){
            //让s[0]匹配t[0]  不让s[0]匹配t[0]     
            res += dp(s,i+1,t,j+1) +dp(s,i+1,t,j);
        }else{
            res+=dp(s,i+1,t,j);
        }
        memo[i][j]=res;
        return res;
    }
    // 递归函数本身时间复杂度O(1), 状态个数O(n*m),总时间复杂度O(1*n*m)=O(m*n)
};

class Solution {
public:
    
    string tmp="";
    int res=0;
    int numDistinct(string s, string t) {
        int n=s.size(),m=t.size();
        dfs(s,0,t);
        return res;
        }
    void dfs(string &s,int i, string &t){
        if(tmp.size()==t.size()&&tmp==t){
            res++;
            return ;
        }

        for(int index=i;index<s.size();index++){
            tmp += s[index];
            dfs(s,index+1,t);
            tmp.pop_back();
        }
    }
};

// @lc code=end

