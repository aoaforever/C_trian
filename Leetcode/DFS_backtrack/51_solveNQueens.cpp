#include <vector>
#include <string>

using namespace std;

class Solution{
public:
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n){
        //新建空白棋盘, .代表空，Q代表皇后
        vector<string> board(n,string(n,'.'));
        backtrack(board,0);
    }
    void backtrack(vector<string>& board, int row){
        //row是判断结束的条件
        if(row == board.size()){
            res.push_back(board);
            return ;
        }
        //col是选择列表
        for(int col = 0 ; col<board.size();col++){
            //判断当前选择行不行，不行就进行下一次循环
            if(!isValid(board,row,col)){
                continue;
            }
            //将选择添加到结果
            board[row][col] = 'Q';
            backtrack(board,row+1);
            //撤销选择
            board[row][col] = '.';
        }
    }
    bool isValid(vector<string>&board, int row, int col){
        //直线与斜角不能有Q
        /*
        因为皇后是⼀⾏⼀⾏从上往下放的，所以左下⽅，右下⽅和正下⽅不⽤检查（还没放皇后）；因为⼀⾏只会
        放⼀个皇后，所以每⾏不⽤检查。也就是最后只⽤检查上⾯，左上，右上三个⽅向
        */
        for(int i=0; i<board.size();i++){//检查当前列有没有Q
            if(board[i][col] == 'Q'){
                return false;
            }
        }
        //左上有没有Q
        for(int i=row-1, j = col-1; i>=0&&j>=0 ;i--,j--){
            if(board[i][j]=='Q') return false;
        }

        //右上有没有Q
        for(int i=row-1, j = col+1; i>=0&&j<board.size(); i--, j++){
            if(board[i][j]=='Q') return false;
        }

        return true;
    }
};

int main(){
    //输入n，输出所有答案，这些答案是string数组
}