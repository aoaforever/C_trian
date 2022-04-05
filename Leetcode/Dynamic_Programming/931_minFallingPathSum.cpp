#include <vector>
#include <limits.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int minFallingPathSum(vector<vector<int>>& matrix) {
        memo = vector<vector<int>>(matrix.size(),vector<int>(matrix[0].size(),666));
        int row = matrix.size();
        int col = matrix[0].size();
        int res = INT_MAX;

        for(int j=0;j<col;j++){
            res= min(res,dp(matrix,row-1,j));//为什么采用从下到上，因为只需要监测是否大于等于0，小于零表示搞完了。
        }
        return res;
    }
    //dp代表当前行和列，所选择的路径和。
    int dp(vector<vector<int>>&matrix,int row,int col){
        //已经选了某个col了，继续往上传递。
        if(col<0||col>matrix[0].size()-1 || row<0 || row> matrix.size()-1) return INT_MAX;
        
        if(row==0) return matrix[row][col];
        if (memo[row][col]!=666) return memo[row][col];
        int res= matrix[row][col]+ 
            min_dp(dp(matrix,row-1,col-1),dp(matrix,row-1,col),dp(matrix,row-1,col+1));

        memo[row][col] = res;
        return memo[row][col];

    }

    int min_dp(int a,int b,int c){
        return min(a,min(b,c));
    }
};