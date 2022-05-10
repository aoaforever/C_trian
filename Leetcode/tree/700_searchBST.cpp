/*
 * @lc app=leetcode.cn id=700 lang=cpp
 *
 * [700] 二叉搜索树中的搜索
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
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
//利⽤ BST 左⼩右⼤的特性，可以避免搜索整棵⼆叉树去寻找元素，从⽽提升效率。
    TreeNode* find;
    TreeNode* searchBST(TreeNode* root, int val) {
        find=nullptr;
        findt(root,val);
        return find;
    }
    void findt(TreeNode* root,int val){
        if(root==NULL) return ;
        if(root->val==val) {
            find=root;
            return;
        }
        if(root->val>val) findt(root->left,val);
        if(root->val<val) findt(root->right,val);
        
    }
};

class Solution {
public:
//利⽤ BST 左⼩右⼤的特性，可以避免搜索整棵⼆叉树去寻找元素，从⽽提升效率。

    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==NULL)  return NULL;
        if(root->val>val) return searchBST(root->left,val);
        if(root->val<val) return searchBST(root->right,val);
        return root;//不然的话当前的就是要找的
    }

};
// @lc code=end

