
/*
221. 最大正方形
在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

 

示例 1：


输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：4




看1227题
*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {//傻逼吧，故意写个char恶心人
        int r= matrix.size(), c = matrix[0].size();
        vector<vector<int>> dp(r,vector<int>(c));
        int max_side=0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(i==0||j==0){
                    dp[i][j] = matrix[i][j]-'0';
                }
                else if(matrix[i][j]=='0'){
                    dp[i][j]=0;
                }
                else {
                    dp[i][j] = min(dp[i][j-1], min(dp[i-1][j],dp[i-1][j-1])) + 1;
                }
                cout<<dp[i][j]<<" ";
                max_side = max(max_side,dp[i][j]);
            }
        }
        return max_side*max_side;
    }
};