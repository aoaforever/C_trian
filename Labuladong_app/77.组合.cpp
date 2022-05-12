/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 *
 * https://leetcode-cn.com/problems/combinations/description/
 *
 * algorithms
 * Medium (77.02%)
 * Likes:    973
 * Dislikes: 0
 * Total Accepted:    345.8K
 * Total Submissions: 448.8K
 * Testcase Example:  '4\n2'
 *
 * 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
 * 
 * 你可以按 任何顺序 返回答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 4, k = 2
 * 输出：
 * [
 * ⁠ [2,4],
 * ⁠ [3,4],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ [1,3],
 * ⁠ [1,4],
 * ]
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1, k = 1
 * 输出：[[1]]
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
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    set<int> used;
    vector<vector<int>> combine(int n, int k) {
        vector<int>path;
        backtrack(1,n,k,path);
        return res;
    }
    void backtrack(int index,int n,int k,vector<int>&path){
        if(path.size()==k){
            res.push_back(path);
            return;
        }
        for(int i=index;i<=n;i++){
            if(used.count(i)) continue;
            used.insert(i);
            path.push_back(i);
            backtrack(i+1,n,k,path);
            path.pop_back();
            used.erase(i);
        }
    }
};
// @lc code=end

