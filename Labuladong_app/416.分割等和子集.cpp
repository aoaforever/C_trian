/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 *
 * https://leetcode-cn.com/problems/partition-equal-subset-sum/description/
 *
 * algorithms
 * Medium (51.64%)
 * Likes:    1322
 * Dislikes: 0
 * Total Accepted:    268.7K
 * Total Submissions: 519K
 * Testcase Example:  '[1,5,11,5]'
 *
 * 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,5,11,5]
 * 输出：true
 * 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,2,3,5]
 * 输出：false
 * 解释：数组不能分割成两个元素和相等的子集。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <numeric>
#include <unordered_map>
#include <string>
using namespace std;
class Solution {
public:
    vector<bool> used;
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%2!=0) return false;
        int target = sum/2;
        sort(nums.begin(),nums.end(),greater<int>());
        used.resize(nums.size(),false);
        return dp(nums,0,target);
    }
    //这种可以跳跃数字的怎么搞？

    //那就是选择所有的nums，组成target一次就可以了
    bool dp(vector<int>&nums,int index,int target){
        if(target==0) return true;

        for(int i = index;i<nums.size();i++){
            if(used[i]) continue;
            if(target-nums[i]<0) continue;//不装入背包                
            else {
                used[i] = true;
                if(dp(nums,i+1,target-nums[i])){
                    return true;
                }//装入背包
                used[i] =false;
            }
        }
        //如果遍历了所有元素都组成不了，那就是错误
        
        return false;
    }
};


//以数字视角，由于只有一个桶，也就是0-1背包，完全优化之后就是下面的下面的解法
class Solution {
public:
    
    unordered_map<string,bool> memo;
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%2!=0) return false;
        int target = sum/2;
        // sort(nums.begin(),nums.end(),greater<int>());

        return dp(nums,0,target);
    }
    //这种可以跳跃数字的怎么搞？

    //那就是选择所有的nums，组成target一次就可以了
    bool dp(vector<int>&nums,int index,int target){
        if(target==0) return true;
        if(target<0||index>=nums.size()) return false;

        string key = to_string(index)+","+to_string(target);
        if(memo.count(key)) return memo[key];
        
        // if(target-nums[index]<0)  res = dp(nums,index+1,target);
        bool res= dp(nums,index+1,target-nums[index])||dp(nums,index+1,target);//顺序不能反
        
        //如果遍历了所有桶都组成不了，那就是错误
        memo[key] =res;
        return res;
    }
};

// class Solution {
// public:
//     unordered_map<string,bool> memo;
//     bool canPartition(vector<int>& nums) {
//         int sum = accumulate(nums.begin(),nums.end(),0);
//         if(sum%2!=0) return false;
//         int target = sum/2;
//         return dp(nums,0,target);
//     }
//     //这种可以跳跃数字的怎么搞？把装与不装体现出来

//     //那就是选择所有的nums，组成target一次就可以了
//     bool dp(vector<int>&nums,int index,int target){
        
//         if(target==0) return true;
//         if(target<0||index==nums.size()) return false;
//         // cout<<index<<endl;
//         string key = to_string(index)+","+to_string(target);
//         if(memo.count(key)) return memo[key];
//         bool res = dp(nums,index+1,target-nums[index])||dp(nums,index+1,target);//你可以装入也可以不装入
//         memo[key] =res;
//         return res;
//     }
// };
// @lc code=end

