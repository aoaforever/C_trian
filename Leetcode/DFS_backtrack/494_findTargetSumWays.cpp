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
#include <unordered_map>
using namespace std;
class Solution {
public:
    int res=0;
    int findTargetSumWays(vector<int>& nums, int target) {
        backtrack(nums,0,target);
        return res;
    }
    void backtrack(vector<int>& nums,int i,int target){
        //i表示到哪个位置了，
        if(i==nums.size()){
            if(target==0)  res++;
            return ;
        }
        //做选择，就两个选择，所以分开写
        //如果是加法，那么target反过来就会被剪掉该值
        target -= nums[i];
        backtrack(nums,i+1,target);
        target += nums[i];

        //如果是减法
        
        target += nums[i];
        backtrack(nums,i+1,target);
        target -= nums[i];
    }
};
// @lc code=end

//怎么找重叠子问题？
    void backtrack(vector<int>& nums,int i,int target){
        //如果nums[i]=0,那么target就没有任何变化，所以重叠了
        backtrack(nums,i+1,target);
        backtrack(nums,i+1,target);
    }


class Solution {
public:
    
    unordered_map<string,int> memo;
    int findTargetSumWays(vector<int>& nums, int target) {
        return backtrack(nums,0,target);
        
    }
    int backtrack(vector<int>& nums,int i,int target){
        //i表示到哪个位置了，
        string m = to_string(i)+","+to_string(target);
        if(memo.count(m)) return memo[m];

        if(i==nums.size()){
            if(target==0)  return 1;
            return 0;
        }
        //做选择，就两个选择，所以分开写
        //如果是加法，那么target反过来就会被剪掉该值
        target -= nums[i];
        int one = backtrack(nums,i+1,target);
        target += nums[i];

        //如果是减法
        
        target += nums[i];
        int two = backtrack(nums,i+1,target);
        target -= nums[i];

        int tmp = one+two;
        
        memo[m] = tmp;
        return memo[m];
    }
};

class Solution {
public:
    
    unordered_map<string,int> memo;
    int findTargetSumWays(vector<int>& nums, int target) {
        return backtrack(nums,0,target);
        
    }
    int backtrack(vector<int>& nums,int i,int target){
        //i表示到哪个位置了，
        string m = to_string(i)+","+to_string(target);
        if(memo.count(m)) return memo[m];

        if(i==nums.size()){
            if(target==0)  return 1;
            return 0;
        }
        // //做选择，就两个选择，所以分开写
        // //如果是加法，那么target反过来就会被剪掉该值
        // target -= nums[i];
        // int one = backtrack(nums,i+1,target);
        // target += nums[i];

        // //如果是减法
        
        // target += nums[i];
        // int two = backtrack(nums,i+1,target);
        // target -= nums[i];

        //再简化一下
        //因为形参不会改变target的值，但是传进去之后下一层的递归的target就变了
        int tmp = backtrack(nums,i+1,target-nums[i])+backtrack(nums,i+1,target+nums[i]);

        // int tmp = one+two;
        
        memo[m] = tmp;
        return memo[m];
    }
};


