/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 *
 * https://leetcode-cn.com/problems/edit-distance/description/
 *
 * algorithms
 * Hard (62.20%)
 * Likes:    2375
 * Dislikes: 0
 * Total Accepted:    255.5K
 * Total Submissions: 410.4K
 * Testcase Example:  '"horse"\n"ros"'
 *
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 * 
 * 你可以对一个单词进行如下三种操作：
 * 
 * 
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：word1 = "horse", word2 = "ros"
 * 输出：3
 * 解释：
 * horse -> rorse (将 'h' 替换为 'r')
 * rorse -> rose (删除 'r')
 * rose -> ros (删除 'e')
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：word1 = "intention", word2 = "execution"
 * 输出：5
 * 解释：
 * intention -> inention (删除 't')
 * inention -> enention (将 'i' 替换为 'e')
 * enention -> exention (将 'n' 替换为 'x')
 * exention -> exection (将 'n' 替换为 'c')
 * exection -> execution (插入 'u')
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= word1.length, word2.length <= 500
 * word1 和 word2 由小写英文字母组成
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Solution {
public:
    int s1,s2;
    vector<vector<int>> memo;
    int minDistance(string word1, string word2) {
        s1=word1.size();
        s2=word2.size();
        memo = vector<vector<int>>(s1,vector<int>(s2,-1));
        return dp(word1,0,word2,0);
    }
    int dp(string& word1,int i,string& word2, int j){
        if(i==s1) return s2-j;
        if(j==s2) return s1-i;


        int res= INT_MAX;   
        if(memo[i][j]!=-1) return memo[i][j];

        if(word1[i]==word2[j]){
            res = dp(word1,i+1,word2,j+1);
        }
        else{
            int replace = dp(word1,i+1,word2,j+1);
            int del = dp(word1,i+1,word2,j);
            int insert = dp(word1,i,word2,j+1);
            res = min(replace,min(del,insert))+1;
        }
        memo[i][j] = res;
        return res;
        
    }
};
// @lc code=end

