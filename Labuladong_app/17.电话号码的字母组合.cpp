/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 *
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (57.76%)
 * Likes:    1887
 * Dislikes: 0
 * Total Accepted:    480.2K
 * Total Submissions: 831.2K
 * Testcase Example:  '"23"'
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 * 
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：digits = "23"
 * 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：digits = ""
 * 输出：[]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：digits = "2"
 * 输出：["a","b","c"]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= digits.length <= 4
 * digits[i] 是范围 ['2', '9'] 的一个数字。
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
using namespace std;
class Solution {
public:
    vector<string> mapping{
        "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"
    };
    vector<string> res;
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){
            return{};
        }
        string sb = "";
        backtrack(digits,0,sb);
        return res;
    }
    void backtrack(string& digits, int start, string&sb){
        if(start==digits.size()){
            //到达回溯树的底部
            res.push_back(sb);
            return;
        }
        // for(int i=start;i<digits.size();i++){
            int digit = digits[start] - '0';
            for(char c:mapping[digit]){
                sb.push_back(c);
                backtrack(digits,start+1,sb);
                sb.pop_back();
            }
        // }

    }
};
// @lc code=end

