/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int> need,window;
        for(auto& c:p){
            need[c]++;
        }
        int l=0,r=0,valid=0;
        vector<int> index;
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
                    index.push_back(l);
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
        return index;
    }
};
// @lc code=end

