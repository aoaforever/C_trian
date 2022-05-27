/*
 * @lc app=leetcode.cn id=312 lang=cpp
 *
 * [312] 戳气球
 *
 * https://leetcode-cn.com/problems/burst-balloons/description/
 *
 * algorithms
 * Hard (69.11%)
 * Likes:    996
 * Dislikes: 0
 * Total Accepted:    74.9K
 * Total Submissions: 108.1K
 * Testcase Example:  '[3,1,5,8]'
 *
 * 有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
 * 
 * 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。 这里的 i
 * - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
 * 
 * 求所能获得硬币的最大数量。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [3,1,5,8]
 * 输出：167
 * 解释：
 * nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
 * coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,5]
 * 输出：10
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == nums.length
 * 1 <= n <= 300
 * 0 <= nums[i] <= 100
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// class Solution {
// public:
//     int res=0;
//     int maxCoins(vector<int>& nums) {
        
//         nums.insert(nums.begin(),1);
//         nums.push_back(1);
//         dp(nums,0);
//         return res;
//     }
//     void dp(vector<int>& nums,int score){
//         if(nums.size()==2) {
//             // cout<<nums[0]<<" "<<nums[1]<<endl;
//             res = max(res,score);
//             return;
//         }

//         for(int i=1;i<nums.size()-1;i++){
//             int points = nums[i-1]*nums[i]*nums[i+1];
//             int tmp = nums[i];
//             nums.erase(nums.begin()+i);
//             dp(nums,score+points);
//             nums.insert(nums.begin()+i,tmp);
//         }
//     }

// };

class Solution {
public:
   
    int maxCoins(vector<int>& nums) {
        
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),0));
        //反向dp
        for(int i=nums.size()-1;i>=0;i--){
            for(int j=i+1;j<nums.size();j++){
                for(int k=i+1;k<j;k++){
                    dp[i][j] = max(dp[i][j],dp[i][k] + dp[k][j] +
                        nums[k]*nums[i]*nums[j]);
                    }
            }
        }
        return dp[0][nums.size()-1];
    }


};
// @lc code=end

