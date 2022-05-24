/*
 * @lc app=leetcode.cn id=787 lang=cpp
 *
 * [787] K 站中转内最便宜的航班
 *
 * https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/description/
 *
 * algorithms
 * Medium (38.94%)
 * Likes:    485
 * Dislikes: 0
 * Total Accepted:    52.5K
 * Total Submissions: 134.8K
 * Testcase Example:  '3\n[[0,1,100],[1,2,100],[0,2,500]]\n0\n2\n1'
 *
 * 有 n 个城市通过一些航班连接。给你一个数组 flights ，其中 flights[i] = [fromi, toi, pricei]
 * ，表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
 * 
 * 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线，使得从 src 到 dst 的
 * 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * 输出: 200
 * 解释: 
 * 城市航班图如下
 * 
 * 
 * 从城市 0 到城市 2 在 1 站中转以内的最便宜价格是 200，如图中红色所示。
 * 
 * 示例 2：
 * 
 * 
 * 输入: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * 输出: 500
 * 解释: 
 * 城市航班图如下
 * 
 * 
 * 从城市 0 到城市 2 在 0 站中转以内的最便宜价格是 500，如图中蓝色所示。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 100
 * 0 <= flights.length <= (n * (n - 1) / 2)
 * flights[i].length == 3
 * 0 <= fromi, toi < n
 * fromi != toi
 * 1 <= pricei <= 10^4
 * 航班没有重复，且不存在自环
 * 0 <= src, dst, k < n
 * src != dst
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<int,vector<vector<int>>> indegree;
    vector<vector<int>> memo;
    int src,dst;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        k = k+1;//k个中转就是k+1条边
        this->src = src;
        this->dst = dst;
        memo = vector<vector<int>>(n,vector<int>(k+1,-666));
        for(vector<int>&f:flights){
            int from = f[0];
            int to =f[1];
            int price = f[2];

            indegree[to].push_back({from,price});
        }
        return dp(dst,k);
    }
    int dp(int i,int k){//定义了到达i的k条边最低价格，那么在哪里更新？
        
        if(i==src){//到达目的地了
            return 0;
        }
        //if的顺序不能乱，如果你中转次数为0了，但是你到了目的地了，那就是成功啊
        if(k==0) return -1;//不允许中转了
        if(memo[i][k]!=-666) return memo[i][k];
        //到达i有许多路径，穷举，求最小值
        auto& from = indegree[i];
        int res = INT_MAX;
        for(vector<int>& f:from){
            int comfrom = f[0];
            int price = f[1];
            int subproblem = dp(comfrom,k-1);
            if(subproblem==-1) continue;//跳过无解情况，不存在这样的路线
            res =min(subproblem+price,res);

        }
        res = res==INT_MAX?-1:res;
        memo[i][k] = res;
        return res;

    }
};
// @lc code=end

