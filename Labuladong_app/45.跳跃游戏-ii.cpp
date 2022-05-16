/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 *
 * https://leetcode-cn.com/problems/jump-game-ii/description/
 *
 * algorithms
 * Medium (44.43%)
 * Likes:    1612
 * Dislikes: 0
 * Total Accepted:    330.1K
 * Total Submissions: 740.4K
 * Testcase Example:  '[2,3,1,1,4]'
 *
 * 给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
 * 
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 
 * 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
 * 
 * 假设你总是可以到达数组的最后一个位置。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [2,3,1,1,4]
 * 输出: 2
 * 解释: 跳到最后一个位置的最小跳跃数是 2。
 * 从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [2,3,0,1,4]
 * 输出: 2
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 
 * 0 
 * 
 * 
 */

// @lc code=start
//根据元素决定往右走几格，最长走
//返回最少步长
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size()==1) return 0;
        vector<int> dp(nums.size(),nums.size()-1);
        dp[0]=0;
        for(int i=0;i<nums.size();i++){
            int val = nums[i];
            for(int j=1;j<=val;j++){
                if(i+j>=nums.size()) continue;
                dp[i+j] = min(dp[i+j],1+dp[i]);
            }
        }
        //遍历完后，dp[4]就是答案。
        return dp[nums.size()-1];
    }
};

class Solution {
public:
    vector<int> memo;
    int jump(vector<int>& nums) {
        memo.resize(nums.size(),-1);
        return dp(nums,0);
        
    }
    int dp(vector<int>&nums,int index){
        //dp[i]代表第i个位置到最后位置的最短步数
        if(index>=nums.size()-1){
            return 0;
        }
        if(memo[index]!=-1) return memo[index];
        int step=nums[index];
        int res=nums.size();
        for(int i=1;i<=step;i++){
            int s = dp(nums,index+i);//最短步数由后面的子问题转移得到
            res= min(res,s+1);//当前的最短步数就是当前的一步加上后面的最短步数
        }
        memo[index] =res;
        return res;

    }
};

class Solution {
public:
    int jump(vector<int>& nums) {
        //记录每个位置能跳跃到的最远位置，取最大值
        int farest=0;
        //当i走到farest的时候，就加步数
        int step=0;
        int end=0;
        for(int i=0;i<nums.size()-1;i++){
            farest = max(farest,nums[i]+i);
            if(end==i){
                end = farest;
                step++;
            }
        }
        return step;
    }
};
// @lc code=end

