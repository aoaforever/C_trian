/*
 * @lc app=leetcode.cn id=104 lang=cpp
 *
 * [104] 二叉树的最大深度
 *
 * https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (76.93%)
 * Likes:    1216
 * Dislikes: 0
 * Total Accepted:    706.5K
 * Total Submissions: 918.3K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给定一个二叉树，找出其最大深度。
 * 
 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 * 
 * 说明: 叶子节点是指没有子节点的节点。
 * 
 * 示例：
 * 给定二叉树 [3,9,20,null,null,15,7]，
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 返回它的最大深度 3 。
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
//动态规划方法，求树的高度
// class Solution {
// public:
//     int res;
//     int maxDepth(TreeNode* root) {
//         dfs(root);
//         return res;
//     }
//     int dfs(TreeNode* root){
//         if(root==NULL) return 0;
//         int left = dfs(root->left);//拆分子问题
//         int right = dfs(root->right);
//         int len = max(left,right)+1;//本层的深度为左右最深的+1
//         res = max(res,len);
//         return len;
//     }
// };


//回溯法，取最深的
class Solution {
public:
    int res;
    int maxDepth(TreeNode* root) {
        backtrack(root,0);
        return res;
    }
    void backtrack(TreeNode* root,int len){
        if(root==NULL){
            res = max(res,len);
            //这里就是知道叶子节点才更新深度
            return;
        }
        
        len++;
        //也可以在这里更新，这里就指的是每条节点都更新一边
        // res = Math.max(res, depth);
        backtrack(root->left,len);
        backtrack(root->right,len);
        len--;
    }

};
// @lc code=end

