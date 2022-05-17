#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int minDistance(string word1, string word2) {
        memo = vector<vector<int>>(word1.size(),vector<int>(word2.size(),-1));
        return dp(word1,0,word2,0);
    }
    int mymin(int a,int b, int c){
        return min(a,min(b,c));
    }
    //dp代表s[i...],s[j...]的最少操作数
    int dp(string& word1,int i, string& word2, int j){
        int res=0;
        if(j==word2.size()){
            //把word1后面的字符删除
            for(;i<word1.size();i++){
                res++;
            }
            return res;
        }

        if(i==word1.size()){
            //增加word2后面的字符
            for(;j<word2.size();j++){
                res++;
            }
            return res;
        }

        if(memo[i][j]!=-1) return memo[i][j];
        if(word1[i]==word2[j]){
            memo[i][j] =  dp(word1,i+1,word2,j+1);
            return memo[i][j];
        }
        else{
            //三种操作，替换、插入、删除
            memo[i][j] =  mymin(1+dp(word1,i+1,word2,j),
                         1+dp(word1,i,word2,j+1),
                         1+dp(word1,i+1,word2,j+1)
            );
            return memo[i][j];
        }
    }
};

class Solution {
public:
    int s1,s2;
    vector<vector<int>> memo;
    int minDistance(string word1, string word2) {
        s1=word1.size();
        s2=word2.size();
        memo = vector<vector<int>>(s1,vector<int>(s2,-1));
        return dp(word1,0,word2,0);
    }
    int dp(string& word1,int i,string& word2, int j){
        if(i==s1) return s2-j;
        if(j==s2) return s1-i;


        int res= INT_MAX;   
        if(memo[i][j]!=-1) return memo[i][j];

        if(word1[i]==word2[j]){
            res = dp(word1,i+1,word2,j+1);
        }
        else{
            int replace = dp(word1,i+1,word2,j+1);
            int del = dp(word1,i+1,word2,j);
            int insert = dp(word1,i,word2,j+1);
            res = min(replace,min(del,insert))+1;
        }
        memo[i][j] = res;
        return res;
        
    }
};