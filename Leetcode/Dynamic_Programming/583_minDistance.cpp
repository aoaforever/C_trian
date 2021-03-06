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

class Solution {
public:
    //同样的，上面能减，下面也能减，最终剪成最长子序列。
    //那么只要知道最长子序列多长，每个原序列-最长子序列就是步数
    int minDistance(string word1, string word2) {
        int len = longestCommonSubsequence(word1,word2);
        return word1.size()-len + word2.size()-len;
    }
    vector<vector<int>> memo;
    int longestCommonSubsequence(string text1, string text2) {
        memo = vector<vector<int>>(text1.size(),vector<int>(text2.size(),-1));
        return dp(text1,text1.size()-1,text2,text2.size()-1);
    }
    int dp(string& text1, int i, string& text2,int j){
        if(i<0||j<0) return 0;
        if(memo[i][j]!=-1) return memo[i][j];

        int res=0;
        if(text1[i]==text2[j]){
            res = 1+dp(text1,i-1,text2,j-1);
            
        }
        else{
            res =  max(dp(text1,i-1,text2,j),dp(text1,i,text2,j-1));
        }
        memo[i][j] =res;
        return res;

    }
};