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


/*
美团笔试 
作者：王悟空
链接：https://www.nowcoder.com/discuss/1021857?type=all&order=recall&pos=&page=1&ncTraceId=&channel=-1&source_id=search_all_nctrack
来源：牛客网

小团生目收到妈妈送的两个一模士样的数列作为礼物！他很开心的把玩，但是不小心没拿稳将数列摔坏了！
现在他手上的两个数列分别为A和B,长度分别为m。小团很想再次让这两个数列变得一样。他现在能做两种操作：
操作一：将一个选定数列中的某一个数a改成数b，这会花费|b-a|的时间
操作二：选择一个数列中某个数a,将它从数列中丢掉，花费a的时间。
小团想知道，他最能以多时间将这两个数列变得再次相同？
 
输入：n、m代表A、B的长度
接下来输入n个整数代表A序列
接下来输入m个整数代表B序列
 
输出最小时间。
 
input:
1 1
-9821
7742
 
output:
17563
*/