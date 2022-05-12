/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 *
 * https://leetcode-cn.com/problems/permutations/description/
 *
 * algorithms
 * Medium (78.52%)
 * Likes:    1996
 * Dislikes: 0
 * Total Accepted:    610K
 * Total Submissions: 776.8K
 * Testcase Example:  '[1,2,3]'
 *
 * 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,3]
 * 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [0,1]
 * 输出：[[0,1],[1,0]]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1]
 * 输出：[[1]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 6
 * -10 <= nums[i] <= 10
 * nums 中的所有整数 互不相同
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    set<int> used;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int>path;
        backtrack(nums,0,path);
        return res;
    }
    void backtrack(vector<int>& nums,int index,vector<int>&path){
        if(index==nums.size()){
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(used.count(nums[i])) continue;
            path.push_back(nums[i]);
            used.insert(nums[i]);
            backtrack(nums,index+1,path);
            path.pop_back();
            used.erase(nums[i]);
        }
    }
};
// @lc code=end

