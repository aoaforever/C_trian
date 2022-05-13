/*
 * @lc app=leetcode.cn id=111 lang=cpp
 *
 * [111] 二叉树的最小深度
 *
 * https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (50.12%)
 * Likes:    731
 * Dislikes: 0
 * Total Accepted:    378.8K
 * Total Submissions: 755.1K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给定一个二叉树，找出其最小深度。
 * 
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * 
 * 说明：叶子节点是指没有子节点的节点。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [3,9,20,null,null,15,7]
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [2,null,3,null,4,null,5,null,6]
 * 输出：5
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点数的范围在 [0, 10^5] 内
 * -1000 
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
#include <queue>
using namespace std;
// class Solution {
// public:
//     int minDepth(TreeNode* root) {
//         if(root==NULL) return 0;
//         queue<TreeNode*> q;
//         q.push(root);
//         int res=1;//记录深度
//         while(!q.empty()){
//             int sz = q.size();
//             for(int i=0;i<sz;i++){
//                 //这一层全遍历，才会进入下一层
//                 TreeNode* sss= q.front();
//                 q.pop();
//                 if(sss->left==NULL&&sss->right==NULL) return res;
//                 if(sss->left!=NULL) q.push(sss->left);
//                 if(sss->right!=NULL) q.push(sss->right);
                
//             }
//             res++;
//         }
//         return res;
//     }
// };

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root==NULL) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int len=1;
        while(!q.empty()){
            int sz = q.size();
            

            for(int i=0;i<sz;i++){
                TreeNode* r = q.front();
                q.pop();
                if(r->left) q.push(r->left);
                if(r->right) q.push(r->right);
                if(r->left==NULL&&r->right==NULL) return len;
            }
            len++;
        }
        return len;
    }
};
// @lc code=end

