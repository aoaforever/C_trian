#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int minimumDeleteSum(string s1, string s2) {
        memo = vector<vector<int>>(s1.size(),vector<int>(s2.size(),-1));
        return  dp(s1,0,s2,0);
        
    }

    //dp代表删除ASCII码的最小和。
    int dp(string& word1, int i , string& word2, int j){

        int res=0;
        if(i==word1.size()){
            for(;j<word2.size();j++){
                res  += word2[j];
            }
            return res;
        }
        if(j==word2.size()){
            for(;i<word1.size();i++){
                res  += word1[i];
            }
            return res;
        }

        if(memo[i][j]!=-1) return memo[i][j];

        if(word1[i]==word2[j]){
            memo[i][j] = dp(word1,i+1,word2,j+1);
            return memo[i][j];
        }
        else {
            memo[i][j] = min(word2[j]+dp(word1,i,word2,j+1), word1[i]+dp(word1,i+1,word2,j));
            return memo[i][j];
        }


    }
};