#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int minDistance(string word1, string word2) {
        memo = vector<vector<int>>(word1.size(),vector<int>(word2.size(),-1));
        int lcs = dp(word1,0,word2,0);
        return word1.size()-lcs+ word2.size()-lcs;
    }

    //dp代表公共子序列的长度
    int dp(string& word1, int i , string& word2, int j){
        if(i>=word1.size()||j>=word2.size()){
            return 0;
        }

        if(memo[i][j]!=-1) return memo[i][j];

        if(word1[i]==word2[j]){
            memo[i][j] =  1+ dp(word1,i+1,word2,j+1);
            return memo[i][j];
        }
        else {
            memo[i][j] = max(dp(word1,i,word2,j+1), dp(word1,i+1,word2,j));
            return memo[i][j];
        }


    }
};