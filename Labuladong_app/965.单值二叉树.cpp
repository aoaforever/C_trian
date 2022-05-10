/*
 * @lc app=leetcode.cn id=965 lang=cpp
 *
 * [965] 单值二叉树
 *
 * https://leetcode-cn.com/problems/univalued-binary-tree/description/
 *
 * algorithms
 * Easy (68.67%)
 * Likes:    110
 * Dislikes: 0
 * Total Accepted:    40.4K
 * Total Submissions: 58.8K
 * Testcase Example:  '[1,1,1,1,1,null,1]'
 *
 * 如果二叉树每个节点都具有相同的值，那么该二叉树就是单值二叉树。
 * 
 * 只有给定的树是单值二叉树时，才返回 true；否则返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：[1,1,1,1,1,null,1]
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：[2,2,2,5,2]
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 给定树的节点数范围是 [1, 100]。
 * 每个节点的值都是整数，范围为 [0, 99] 。
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
//只要res变成了false，就退出
//笨方法，如果左右子树都为true，则判断当前是否为true。如果左右其中有一个为false，则都为false
    bool res=true;
    bool isUnivalTree(TreeNode* root) {
        return dfs(root);
        
    }
    bool dfs(TreeNode* root){
        if(root==NULL) return true;
        if(root->left==NULL&&root->right==NULL) return true;
        bool left = dfs(root->left);
        bool right = dfs(root->right);
        if(left==false||right==false) return false;
        if(root->left&&root->val!=root->left->val||root->right&&root->val!=root->right->val) return false;
        return true;

    }
};
class Solution {
public:
//只要res变成了false，就退出
    bool res;
    int pre_val;
    bool isUnivalTree(TreeNode* root) {
        res = true;
        pre_val = root->val;
        dfs(root);
        return res;
        
    }
    void dfs(TreeNode* root){
        if(root==NULL) return;
        if(res==false) return;//如果res是false，那就不干任何事情，返回

        if(pre_val!=root->val){
            res = false;
            return;//不再遍历。
        }
        dfs(root->left);
        dfs(root->right);

    }
};
// @lc code=end

