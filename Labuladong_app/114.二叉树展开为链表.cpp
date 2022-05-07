/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
 *
 * https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/description/
 *
 * algorithms
 * Medium (72.79%)
 * Likes:    1157
 * Dislikes: 0
 * Total Accepted:    249.4K
 * Total Submissions: 342.6K
 * Testcase Example:  '[1,2,5,3,4,null,6]'
 *
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 * 
 * 
 * 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [1,2,5,3,4,null,6]
 * 输出：[1,null,2,null,3,null,4,null,5,null,6]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = []
 * 输出：[]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：root = [0]
 * 输出：[0]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中结点数在范围 [0, 2000] 内
 * -100 
 * 
 * 
 * 
 * 
 * 进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？
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
    void flatten(TreeNode* root) {
        if(root==NULL) return ;
        flatten(root->left);
        flatten(root->right);
        if(root->left==NULL&&root->right==NULL) return ;//叶子节点直接return
        //两个节点都在
        if(root->left&&root->right){

            TreeNode* tmp = root->right;
            // root->left->right = tmp;
            root->right = root->left;
            root->left = NULL;
            TreeNode* n=root;
            while(n->right!=NULL){
                n=n->right;
            }
            n->right = tmp;
        }
        //只有左节点
        else if(root->left&&root->right==NULL){
            root->right= root->left;
            root->left = NULL;
        }
        //只有右节点
        else if(root->right&&root->left==NULL){
            return;
        }

    }
};
// @lc code=end

