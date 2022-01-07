#include <vector>
#include <string>
using namespace std;

/*给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。
如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-search
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
class Solution{
public:
    vector<int> direction{-1,0,1,0,-1};
    bool exist(vector<vector<char>>& board, string word){
        //同一个单元格内的字母不允许被重复使用。 
        bool find =false;
        vector<vector<bool>> visited(board.size(),vector<bool>(board[0].size(),false));   
        for(int i =0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                backtrack(board,word,visited,i,j,find,0);
            }
        }
        return find;
    }

    void backtrack(vector<vector<char>>& board, string &word, vector<vector<bool>>& visited,int i, int j , bool &find, int pos){
        //不管三七二十一，先递归下去，在判断边界
        if(i<0||i>=board.size()||j<0||j>=board[0].size()){
            return;//超过变界啥也不干，返回
        }

        if(board[i][j]!= word[pos]||visited[i][j]||find){
            return;//如果不是要找的字母，返回
            //如果访问过了，返回
            //如果find=true，返回
        }

        if(pos==word.size()-1){
            find=true;
            return;//如果全部招满了，find=ture，返回
        }

        visited[i][j]=true;
        // for(int k=0;k<4;k++){
        //     int x = i+direction[k], y = j+direction[k+1];
        //     backtrack(board,word,visited,x,y,find,pos+1);
        // }

        backtrack(board,word,visited,i+1,j,find,pos+1);
        backtrack(board,word,visited,i,j+1,find,pos+1);
        backtrack(board,word,visited,i-1,j,find,pos+1);
        backtrack(board,word,visited,i,j-1,find,pos+1);

        visited[i][j]=false;
    }
};