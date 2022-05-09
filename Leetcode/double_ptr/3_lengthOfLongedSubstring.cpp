#include <string>
#include <unordered_map>
using namespace std;

//给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。


class Solution{
public:
    int lengthOfLongestSubstring(string s){
        unordered_map<char,int> window;

        int left=0, right=0;
        int ans;

        while(right<s.size()){
            char c = s[right];
            right++;
            
            window[c]++;
            while(window[c]>1){
                char d = s[left];
                left++;
                window[d]--;
            }
            ans = max(ans,right-left);
        }
        return ans;
    }

};