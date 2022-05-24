/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 *
 * https://leetcode-cn.com/problems/target-sum/description/
 *
 * algorithms
 * Medium (49.03%)
 * Likes:    1202
 * Dislikes: 0
 * Total Accepted:    223K
 * Total Submissions: 454.7K
 * Testcase Example:  '[1,1,1,1,1]\n3'
 *
 * 给你一个整数数组 nums 和一个整数 target 。
 * 
 * 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
 * 
 * 
 * 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
 * 
 * 
 * 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1,1,1], target = 3
 * 输出：5
 * 解释：一共有 5 种方法让最终目标和为 3 。
 * -1 + 1 + 1 + 1 + 1 = 3
 * +1 - 1 + 1 + 1 + 1 = 3
 * +1 + 1 - 1 + 1 + 1 = 3
 * +1 + 1 + 1 - 1 + 1 = 3
 * +1 + 1 + 1 + 1 - 1 = 3
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1], target = 1
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 0 
 * -1000 
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
using namespace std;
// class Solution {
// public:
    
//     unordered_map<string,int> memo;
//     int findTargetSumWays(vector<int>& nums, int target) {
//         return backtrack(nums,0,target);
        
//     }
//     int backtrack(vector<int>& nums,int i,int target){
//         //i表示到哪个位置了，
//         string m = to_string(i)+","+to_string(target);
//         if(memo.count(m)) return memo[m];

//         if(i==nums.size()){
//             if(target==0)  return 1;
//             return 0;
//         }
//         // //做选择，就两个选择，所以分开写
//         // //如果是加法，那么target反过来就会被剪掉该值
//         // target -= nums[i];
//         // int one = backtrack(nums,i+1,target);
//         // target += nums[i];

//         // //如果是减法
        
//         // target += nums[i];
//         // int two = backtrack(nums,i+1,target);
//         // target -= nums[i];

//         //再简化一下
//         //因为形参不会改变target的值，但是传进去之后下一层的递归的target就变了
//         int tmp = backtrack(nums,i+1,target-nums[i])+backtrack(nums,i+1,target+nums[i]);

//         // int tmp = one+two;
        
//         memo[m] = tmp;
//         return memo[m];
//     }
// };

#include <numeric>
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target){
        //两个背包，+ ,  -
        //不同顺序放进这两个背包，它们的总和为target，则res++;
        int sum = accumulate(nums.begin(),nums.end(),0);
        //这两种情况，不可能存在合法的子集划分
        if(sum<abs(target)|| (sum+target)%2==1){
            return 0;
            /*
            测试用例
            [100]
            -200*/
        }
        return subset(nums, (sum+target)/2);
    }
    /*
    回想刚才的 dp 数组含义，可以根据「选择」对 dp[i][j] 得到以下状态转移：
如果不把 nums[i] 算入子集，或者说你不把这第 i 个物品装入背包，那么恰好装满背包的方法数就取决于上一个状态 dp[i-1][j]，继承之前的结果。
如果把 nums[i] 算入子集，或者说你把这第 i 个物品装入了背包，那么只要看前 i - 1 个物品有几种方法可以装满 j - nums[i-1] 的重量就行了，所以取决于状态 dp[i-1][j-nums[i-1]]。
    */
    int subset(vector<int>&nums,int target){
        vector<vector<int>> dp(nums.size()+1,vector<int>(target+1));
        for(int i=0;i<dp.size();i++){
            dp[i][0] = 1;
        }
        // dp[0][0]=1;
        for(int i=1;i<dp.size();i++){
            for(int j =0; j<dp[0].size();j++){
                if(j<nums[i-1]) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i-1][j] +   dp[i-1][j-nums[i-1]];
            }
        }
        return dp[nums.size()][target];
    }

};
// @lc code=end

