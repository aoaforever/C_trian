/*
1277. 统计全为 1 的正方形子矩阵
给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。

 

示例 1：

输入：matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
输出：15
解释： 
边长为 1 的正方形有 10 个。
边长为 2 的正方形有 4 个。
边长为 3 的正方形有 1 个。
正方形的总数 = 10 + 4 + 1 = 15.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/count-square-submatrices-with-all-ones
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

https://leetcode.cn/problems/count-square-submatrices-with-all-ones/solution/tong-ji-quan-wei-1-de-zheng-fang-xing-zi-ju-zhen-2/
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int r= matrix.size(), c = matrix[0].size();
        vector<vector<int>> dp(r,vector<int>(c));
        int ans=0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(i==0||j==0){
                    dp[i][j] = matrix[i][j];
                }
                else if(matrix[i][j]==0){
                    dp[i][j]=0;
                }
                else {
                    dp[i][j] = min(dp[i][j-1], min(dp[i-1][j],dp[i-1][j-1])) + 1;
                }
                ans += dp[i][j];
            }
        }
        return ans;
    }
};