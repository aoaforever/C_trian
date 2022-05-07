/*
 * @lc app=leetcode.cn id=567 lang=cpp
 *
 * [567] 字符串的排列
 *
 * https://leetcode-cn.com/problems/permutation-in-string/description/
 *
 * algorithms
 * Medium (43.74%)
 * Likes:    647
 * Dislikes: 0
 * Total Accepted:    180K
 * Total Submissions: 411.5K
 * Testcase Example:  '"ab"\n"eidbaooo"'
 *
 * 给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的排列。如果是，返回 true ；否则，返回 false 。
 * 
 * 换句话说，s1 的排列之一是 s2 的 子串 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s1 = "ab" s2 = "eidbaooo"
 * 输出：true
 * 解释：s2 包含 s1 的排列之一 ("ba").
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s1= "ab" s2 = "eidboaoo"
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s1.length, s2.length <= 10^4
 * s1 和 s2 仅包含小写字母
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
//s1短，s2长
//s长，t短
class Solution {
public:
    bool checkInclusion(string p, string s) {
        unordered_map<char,int> need,window;
        for(auto& c:p){
            need[c]++;
        }
        int l=0,r=0,valid=0;
        // vector<int> index;
        while(r<s.size()){
            char c = s[r++];
            if(need.count(c)) {
                window[c]++;
                if(window[c]==need[c]){
                    valid++;
                }
            }
            while(r-l>=p.size()){
                if(valid==need.size()){
                    return true;
                }
                
                char d = s[l++];
                if(need.count(d)){
                    if(window[d]==need[d]){
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        return false;
    }
};
// @lc code=end

