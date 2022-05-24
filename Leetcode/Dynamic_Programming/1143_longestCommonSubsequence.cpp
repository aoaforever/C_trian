#include <string>
#include <vector>
using namespace std;
 
     
//最长公共子序列。
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        int z = max(n,m);
        vector<vector<int>> memo(z,vector<int>(z,-1));
        return dp(text1,0,text2,0,memo);
    }

    //肯定用双指针，分别指向两个字串
    //表示当前位置之后的公共子序列的最长长度。
    int dp(string text1, int i , string text2, int j,vector<vector<int>>& memo){
        if(i==text1.size()||j==text2.size()){
            return 0;
        }

        if(memo[i][j]!=-1){
            return memo[i][j];
        }
        //如果当前字符相同，则长度加一，并继续递归下去。
        //可以看出是前序
        if(text1[i]==text2[j]){
            memo[i][j] = 1+ dp(text1,i+1,text2,j+1,memo);
            
        }
        else{
            memo[i][j] = max(
                dp(text1,i,text2,j+1,memo),
                dp(text1,i+1,text2,j,memo));
            
        }

        return memo[i][j];
    }
};

//自底向上
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        //明确dp的定义
        //定义：dp[i][j]表示text1[0..i-1],text2[0..j-1]的lcs长度。
        int n = text1.size();
        int m= text2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(text1[i-1]==text2[j-1]){
                    dp[i][j] = 1+dp[i-1][j-1];
                }
                else {
                    dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
        return dp[n][m];

    }


};

class Solution {
public:
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