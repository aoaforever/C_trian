/*https://leetcode.cn/problems/word-break/
139. 单词拆分
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

 

示例 1：

输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
示例 2：

输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
     注意，你可以重复使用字典中的单词。
示例 3：

输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
//回溯法，超时
class Solution {
public:
    //虽然是回溯，但是题目也没要求我输出所有合格的结果，所以就不用存储中间结果了吖

    bool wordBreak(string s, vector<string>& wordDict) {
        return backtrack(s,wordDict,0);
    }

    bool backtrack(string& s, vector<string>& wordDict,int i){
        if(i==s.size()) return true;

        for(string& w:wordDict){
            int len = w.size();
            if(s.substr(i,len)==w){
                if(backtrack(s,wordDict,i+len)==true) return true;
            }
        }
        return false;
    }

};

//dp法，居然没有多大的改动，可能是回溯法写的太像dp了，只加个memo就解决了
class Solution {
public:
    //dp
    vector<int> memo;
    bool wordBreak(string s, vector<string>& wordDict) {
        memo.resize(s.size()+1,-1);
        return backtrack(s,wordDict,0);
    }

    bool backtrack(string& s, vector<string>& wordDict,int i){
        if(i==s.size()) {
            memo[i] = 1;
            return true;
        }
        if(memo[i]!=-1) return memo[i];
        for(string& w:wordDict){
            int len = w.size();
            if(s.substr(i,len)==w){
                if(backtrack(s,wordDict,i+len)==true) {
                    memo[i] =1;
                    return true;
                }
            }
        }
        memo[i] =0;
        return false;
    }

};