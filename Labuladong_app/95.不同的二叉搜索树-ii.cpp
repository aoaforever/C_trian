/*
 * @lc app=leetcode.cn id=95 lang=cpp
 *
 * [95] 不同的二叉搜索树 II
 *
 * https://leetcode-cn.com/problems/unique-binary-search-trees-ii/description/
 *
 * algorithms
 * Medium (71.76%)
 * Likes:    1204
 * Dislikes: 0
 * Total Accepted:    130.1K
 * Total Submissions: 180.8K
 * Testcase Example:  '3'
 *
 * 给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树 。可以按 任意顺序 返回答案。
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 3
 * 输出：[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 1
 * 输出：[[1]]
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
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return build(1,n);
    }

    vector<TreeNode*> build(int lo,int hi){//[lo,hi]
        vector<TreeNode*> res;
        if(lo>hi){
            //当空集的时候
            res.push_back(NULL);
            return res;
        }
        for(int mid =lo; mid<=hi;mid++){
            vector<TreeNode*> left = build(lo,mid-1);
            vector<TreeNode*> right = build(mid+1,hi);

            for(auto l:left){
                for(auto r:right){
                    TreeNode* root = new TreeNode(mid);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
// @lc code=end

