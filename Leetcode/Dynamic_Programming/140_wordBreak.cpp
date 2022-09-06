/*
140. 单词拆分 II
给定一个字符串 s 和一个字符串字典 wordDict ，在字符串 s 中增加空格来构建一个句子，使得句子中所有的单词都在词典中。以任意顺序 返回所有这些可能的句子。

注意：词典中的同一个单词可能在分段中被重复使用多次。

 

示例 1：

输入:s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
输出:["cats and dog","cat sand dog"]
示例 2：

输入:s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
输出:["pine apple pen apple","pineapple pen apple","pine applepen apple"]
解释: 注意你可以重复使用字典中的单词。
示例 3：

输入:s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
输出:[]
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    unordered_map<int,vector<string>> memo;
    unordered_set<string> word;

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        word = unordered_set(wordDict.begin(),wordDict.end());
        dp(s,wordDict,0);
        return memo[0];
        
    }
    vector<string> dp(string&s, vector<string>& wordDict, int i){
        vector<string> res;
        if(i==s.size()){
            res.push_back("");
            memo[i]=res;
            return res;
        }
        if(memo.count(i)) return memo[i];

        
        for(int len =1; len+i <= s.size();len++){
            string pref = s.substr(i,len);
            if(word.count(pref)){
                vector<string> ret = dp(s,wordDict,i+len);
                    for(string& r :ret){
                        if(r.empty()) res.push_back(pref);
                        else{
                            //不是pref += " " + r;
                            //因为如果有多个r，那么pref就会被修改，从而得不到正确答案
                            res.push_back(pref + " "+r);
                        }
                    }
            }
        }

        memo[i] = res;
        return res;

    }
};