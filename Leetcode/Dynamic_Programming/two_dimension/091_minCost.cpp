/*
剑指 Offer II 091. 粉刷房子
假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。

当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。每个房子粉刷成不同颜色的花费是以一个 n x 3 的正整数矩阵 costs 来表示的。

例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。

请计算出粉刷完所有房子最少的花费成本。

 

示例 1：

输入: costs = [[17,2,17],[16,16,5],[14,3,19]]
输出: 10
解释: 将 0 号房子粉刷成蓝色，1 号房子粉刷成绿色，2 号房子粉刷成蓝色。
     最少花费: 2 + 5 + 3 = 10。
示例 2：

输入: costs = [[7,6,2]]
输出: 2

*/
class Solution {
public:
    int r,c;
    vector<vector<int>> memo;
    int minCost(vector<vector<int>>& costs) {
        memo.resize(costs.size(),vector<int>(3,-666));
        r = costs.size();
        c = costs[0].size();
        int res=INT_MAX;
        for(int j=0;j<3;j++){
            // int sub = costs[0][j];
            res = min(res,dp(costs,0,j));//i从1开始，这里先选其中3列,j代表上一列选了什么？
        }
        // res= dp(costs,0,j);
        return res;
    }
    int dp(vector<vector<int>>& costs, int i, int j){
        
        if(i==r){
            return 0;
        }
        if(memo[i][j]!=-666) return memo[i][j];
        int sub=INT_MAX;
        for(int jj=0;jj<3;jj++){
            if(jj==j) continue;
            sub = min(sub,dp(costs,i+1,jj));
        }
        // res = min(res,dp(costs,i+1,j!=j的所有列));
        memo[i][j]=sub+costs[i][j];
        return memo[i][j];

    }
};