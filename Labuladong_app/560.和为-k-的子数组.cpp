/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 *
 * https://leetcode-cn.com/problems/subarray-sum-equals-k/description/
 *
 * algorithms
 * Medium (45.02%)
 * Likes:    1450
 * Dislikes: 0
 * Total Accepted:    216.7K
 * Total Submissions: 481.4K
 * Testcase Example:  '[1,1,1]\n2'
 *
 * 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,1,1], k = 2
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,3], k = 3
 * 输出：2
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * -1000 <= nums[i] <= 1000
 * -10^7 <= k <= 10^7
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
//     int subarraySum(vector<int>& nums, int k) {
//         vector<int> preNum(nums.size()+1,0);
//         for(int i=1;i<preNum.size();i++){
//             preNum[i] = preNum[i-1] + nums[i-1];
//         }

//         int res =0;
//         for(int i=0;i<preNum.size();i++){
//             for(int j=0;j<i;j++){
//                 if(preNum[i]-preNum[j]==k){
//                     res++;
//                 }
//             }
//         }
//         return res;

//     }
// };
#include <unordered_map>
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> preNum;
        preNum[0]=1;//关键
        int sum=0,res=0;
        for(int i=0;i<nums.size();i++){
            sum += nums[i];//前缀和
            int sum_j = sum -k;//
            if(preNum.count(sum_j)){//如果有前缀和满足sum-k
                res += preNum[sum_j];//找出这个前缀和的次数加上
            }
            preNum[sum]++;//给改前缀和+1
        }

        
        return res;

    }
};
// @lc code=end

