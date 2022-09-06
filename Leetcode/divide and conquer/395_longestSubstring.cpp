#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Solution {
public:
    int longestSubstring(string s, int k) {
        return dfs(s,k);
    }

    int dfs(string s, int k){
        if(s.empty()||s.size()==0||s.size()<k) return 0;

        vector<int> freq(26,0);
        for(char a:s){
            freq[a-'a']++;
        }
        for(int i=0;i<s.size();i++){
            if(freq[s[i]-'a']<k){
                return max(
                    dfs(s.substr(0,i),k),
                    dfs(s.substr(i+1),k)
                );
            };
        }
        return s.size();
    }
};

/*
"weitong"
2
*/

int main(int argc, char const *argv[])
{
    Solution s;
    cout<<s.longestSubstring("weitong",2);
    return 0;
}
