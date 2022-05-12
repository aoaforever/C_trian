/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 *
 * https://leetcode-cn.com/problems/unique-binary-search-trees/description/
 *
 * algorithms
 * Medium (70.15%)
 * Likes:    1749
 * Dislikes: 0
 * Total Accepted:    242.7K
 * Total Submissions: 345.7K
 * Testcase Example:  '3'
 *
 * 给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 3
 * 输出：5
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
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
    vector<vector<int>> memo;
    int numTrees(int n) {
        memo = vector<vector<int>>(n+1,vector<int>(n+1,-1));
        return build(1,n);
    }
    int build(int lo, int hi){
        //[lo,hi]构建bST的个数
        if(lo>hi) return 1;//空集也是一种情况
        if(memo[lo][hi]!=-1) return memo[lo][hi]; 
        int res =0;
        for(int i=lo;i<=hi;i++){
            int left = build(lo,i-1);
            int right = build(i+1,hi);
            //选用当前位置i，则左区间就是左子树，右区间就是右子树。
            res += left*right;//所有i遍历完，每个元素都成为根了，就得到最终的答案。
        }
        memo[lo][hi] =res;
        return res;
    }
};
// @lc code=end

