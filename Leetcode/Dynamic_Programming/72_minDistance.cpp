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