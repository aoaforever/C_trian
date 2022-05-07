#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution{
public:
    vector<int> findAnagrams(string s, string p){
        // unordered_map<char,int> need,window;
        vector<int> need(26,0),window(26,0);
        int size=0;
        for(char c:p){
            // ++need[c];
            if(need[c-'a']==0){
                size++;
            }
            ++need[c-'a'];

        }

        int left=0,right=0,valid=0;
        vector<int> ans;
        while(right<s.size()){
            char c = s[right];
            right++;

            if(need[c-'a']!=0){
                // window[c]++;
                window[c-'a']++;
                if(need[c-'a']==window[c-'a']){//当找到所有重复的字母时，有效++。
                    valid++;
                }
            }

            while(right-left>=p.size()){
                if(valid==size){
                    //更新结果
                    ans.push_back(left);
                }

                char d =s[left];
                left++;

                if(need[d-'a']!=0){
                    if(need[d-'a']==window[d-'a']){
                        --valid;
                    }
                    // window[d]--;
                    window[d-'a']--;
                }
            }
        }
        return ans;
    }

};


