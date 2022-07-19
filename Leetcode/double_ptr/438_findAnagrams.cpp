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


//二刷不会，忘了哈希表要几个，忘了什么时候给窗口加1
/***********/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int> n,window;

        for(char& c:p){
            n[c]++;
        }
        int need = n.size();
        vector<int> res;
        int l=0,r=0;
        int m=s.size();
        int valid=0;
        while(l<m&&r<m){
            char c = s[r++];
            if(n.count(c)){
                window[c]++;
                if(window[c]==n[c]){
                    valid++;
                }
            }
            while((r-l)>=p.size()){
                if(valid==n.size()){
                    res.push_back(l);
                }
                char d = s[l++];
                if(n.count(d)){
                    if(window[d]==n[d]){
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        return res;
    }
};