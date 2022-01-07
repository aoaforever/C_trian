#include <vector>

using namespace std;

class NumMatrix {
private:
    vector<vector<int>> preSum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n= matrix[0].size();
        if(m==0||n==0) return;
        //构造前缀和矩阵
        preSum.resize(m+1,vector<int>(n+1));
        for(int i =1; i<=m; i++){
            for(int j=1; j<= n; j++){
                //计算每个矩阵[0,0,i,j]的元素和
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] + matrix[i-1][j-1] - preSum[i-1][j-1];
            }
        }
        
    }
    
    //计算子矩阵[x1,y1,x2,y2]的元素和
    int sumRegion(int row1, int col1, int row2, int col2) {
        return preSum[row2+1][col2+1]-preSum[row1][col2+1] - preSum[row2+1][col1] + preSum[row1][col1];
    }
};