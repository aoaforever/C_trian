/*
 * @lc app=leetcode.cn id=583 lang=cpp
 *
 * [583] 两个字符串的删除操作
 *
 * https://leetcode-cn.com/problems/delete-operation-for-two-strings/description/
 *
 * algorithms
 * Medium (64.44%)
 * Likes:    425
 * Dislikes: 0
 * Total Accepted:    79K
 * Total Submissions: 122K
 * Testcase Example:  '"sea"\n"eat"'
 *
 * 给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
 * 
 * 每步 可以删除任意一个字符串中的一个字符。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入: word1 = "sea", word2 = "eat"
 * 输出: 2
 * 解释: 第一步将 "sea" 变为 "ea" ，第二步将 "eat "变为 "ea"
 * 
 * 
 * 示例  2:
 * 
 * 
 * 输入：word1 = "leetcode", word2 = "etco"
 * 输出：4
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 
 * 1 <= word1.length, word2.length <= 500
 * word1 和 word2 只包含小写英文字母
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
    //同样的，上面能减，下面也能减，最终剪成最长子序列。
    //那么只要知道最长子序列多长，每个原序列-最长子序列就是步数
    int minDistance(string word1, string word2) {
        int len = longestCommonSubsequence(word1,word2);
        return word1.size()-len + word2.size()-len;
    }
    vector<vector<int>> memo;
    int longestCommonSubsequence(string text1, string text2) {
        memo = vector<vector<int>>(text1.size(),vector<int>(text2.size(),-1));
        return dp(text1,text1.size()-1,text2,text2.size()-1);
    }
    int dp(string& text1, int i, string& text2,int j){
        if(i<0||j<0) return 0;
        if(memo[i][j]!=-1) return memo[i][j];

        int res=0;
        if(text1[i]==text2[j]){
            res = 1+dp(text1,i-1,text2,j-1);
            
        }
        else{
            res =  max(dp(text1,i-1,text2,j),dp(text1,i,text2,j-1));
        }
        memo[i][j] =res;
        return res;

    }
};
// @lc code=end

