/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 *
 * https://leetcode-cn.com/problems/climbing-stairs/description/
 *
 * algorithms
 * Easy (53.60%)
 * Likes:    2424
 * Dislikes: 0
 * Total Accepted:    827.1K
 * Total Submissions: 1.5M
 * Testcase Example:  '2'
 *
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 * 
 * 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 2
 * 输出：2
 * 解释：有两种方法可以爬到楼顶。
 * 1. 1 阶 + 1 阶
 * 2. 2 阶
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 3
 * 输出：3
 * 解释：有三种方法可以爬到楼顶。
 * 1. 1 阶 + 1 阶 + 1 阶
 * 2. 1 阶 + 2 阶
 * 3. 2 阶 + 1 阶
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 45
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int climbStairs(int n) {
        //不是求步数，而是求方法
        //斐波那契数列
        // vector<int> dp(n+1);
        // dp[0] =0;
        // dp[1] = 1;
        // dp[2] = 2;//第二个台阶也很简单

        int dp_i=2,dp_i_1=2,dp_i_2=1;
        for(int i=3;i<=n;i++){
            // dp[i] = dp[i-1]+dp[i-2];
            dp_i = dp_i_1+dp_i_2;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
            cout<<dp_i<<endl;
        }
        return n<=2?n:dp_i;
    }
};
// @lc code=end

