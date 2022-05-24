/*
 * @lc app=leetcode.cn id=712 lang=cpp
 *
 * [712] 两个字符串的最小ASCII删除和
 *
 * https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
 *
 * algorithms
 * Medium (67.59%)
 * Likes:    274
 * Dislikes: 0
 * Total Accepted:    21.9K
 * Total Submissions: 32.3K
 * Testcase Example:  '"sea"\n"eat"'
 *
 * 给定两个字符串s1 和 s2，返回 使两个字符串相等所需删除字符的 ASCII 值的最小和 。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: s1 = "sea", s2 = "eat"
 * 输出: 231
 * 解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
 * 在 "eat" 中删除 "t" 并将 116 加入总和。
 * 结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: s1 = "delete", s2 = "leet"
 * 输出: 403
 * 解释: 在 "delete" 中删除 "dee" 字符串变成 "let"，
 * 将 100[d]+101[e]+101[e] 加入总和。在 "leet" 中删除 "e" 将 101[e] 加入总和。
 * 结束时，两个字符串都等于 "let"，结果即为 100+101+101+101 = 403 。
 * 如果改为将两个字符串转换为 "lee" 或 "eet"，我们会得到 433 或 417 的结果，比答案更大。
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 0 <= s1.length, s2.length <= 1000
 * s1 和 s2 由小写英文字母组成
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
    vector<vector<int>> memo;
    int minimumDeleteSum(string s1, string s2) {
        memo = vector<vector<int>>(s1.size(),vector<int>(s2.size(),-1));
        return dp(s1,s1.size()-1,s2,s2.size()-1);
    }
    int dp(string& s1, int i, string& s2, int j){
        //表示最小ASCII和
        if(i<0) {
            //把s2剩下的全删了
            int sum=0;
            for(int k=j;k>=0;k--){
                sum += int(s2[k]);
            }
            return sum;
        }
        if(j<0){
            //把s2剩下的全删了
            int sum=0;
            for(int k=i;k>=0;k--){
                sum += int(s1[k]);
            }
            return sum;
        }

        if(memo[i][j]!=-1) return memo[i][j];
        if(s1[i]==s2[j]){
            memo[i][j] = dp(s1,i-1,s2,j-1);//相等不用删除
        }
        else{
            memo[i][j]= min(
                int(s1[i])+dp(s1,i-1,s2,j),
                int(s2[j])+dp(s1,i,s2,j-1)
            );
        }
        return memo[i][j];

    }
};
// @lc code=end

