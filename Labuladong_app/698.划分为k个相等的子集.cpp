/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 *
 * https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/description/
 *
 * algorithms
 * Medium (42.00%)
 * Likes:    556
 * Dislikes: 0
 * Total Accepted:    46.3K
 * Total Submissions: 110.7K
 * Testcase Example:  '[4,3,2,3,5,2,1]\n4'
 *
 * 给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 * 输出： True
 * 说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [1,2,3,4], k = 3
 * 输出: false
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= k <= len(nums) <= 16
 * 0 < nums[i] < 10000
 * 每个元素的频率在 [1,4] 范围内
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
class Solution {
public:
    vector<bool> used;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        used.resize(nums.size(),false);
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%k!=0) return false;
        int target = sum/k;
        return backtrack(nums,0,k,0,target);
    }
    bool backtrack(vector<int>& nums,int start, int k,int bucket, int target){
        //k个桶，每个桶容量为nums/k
        if(k==0){
            return true;
        }

        if(bucket == target){
            return backtrack(nums,0,k-1,0,target);
        }
        for(int i=start;i<nums.size();i++){
            if(used[i]) continue;
            if(bucket+nums[i]>target) continue;
            used[i]=true;
            bucket += nums[i];
            if(backtrack(nums,i+1,k,bucket,target))
            {
                return true;
            }
            bucket -= nums[i];
            used[i] = false;
            
        }
        return false;
    }
};
// @lc code=end

