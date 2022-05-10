/*
 * @lc app=leetcode.cn id=1373 lang=cpp
 *
 * [1373] 二叉搜索子树的最大键值和
 *
 * https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/description/
 *
 * algorithms
 * Hard (41.69%)
 * Likes:    96
 * Dislikes: 0
 * Total Accepted:    13.8K
 * Total Submissions: 33.1K
 * Testcase Example:  '[1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]'
 *
 * 给你一棵以 root 为根的 二叉树 ，请你返回 任意 二叉搜索子树的最大键值和。
 * 
 * 二叉搜索树的定义如下：
 * 
 * 
 * 任意节点的左子树中的键值都 小于 此节点的键值。
 * 任意节点的右子树中的键值都 大于 此节点的键值。
 * 任意节点的左子树和右子树都是二叉搜索树。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
 * 输出：20
 * 解释：键值为 3 的子树是和最大的二叉搜索树。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：root = [4,3,null,1,2]
 * 输出：2
 * 解释：键值为 2 的单节点子树是和最大的二叉搜索树。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：root = [-4,-2,-5]
 * 输出：0
 * 解释：所有节点键值都为负数，和最大的二叉搜索树为空。
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：root = [2,1,3]
 * 输出：6
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：root = [5,4,8,3,null,6,3]
 * 输出：7
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 每棵树有 1 到 40000 个节点。
 * 每个节点的键值在 [-4 * 10^4 , 4 * 10^4] 之间。
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
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*

示例 3：

输入：root = [-4,-2,-5]
输出：0
解释：所有节点键值都为负数，和最大的二叉搜索树为空。
*/
class Solution {
public:
    int res;
    int maxSumBST(TreeNode* root) {
        res=0;
        dfs(root);
        return res;
    }
    vector<int> dfs(TreeNode* root){
        //更新BST的所有节点和
        if(root==NULL) return{1,INT_MAX,INT_MIN,0};
        //[BST,min,max,sum]
        vector<int> left = dfs(root->left);
        vector<int> right = dfs(root->right);
        vector<int> tmp(4);
        if(left[0]==1&&right[0]==1&&root->val>left[2]&&root->val<right[1]){
            //当前节点也是BST
            
            tmp[0]=1;
            //记录以root为根的这颗BST的最小值
            tmp[1] = min(root->val,left[1]);//最小值。
            //记录以root为根 的这颗bst的最大值
            tmp[2] = max(root->val,right[2]);//最大值
            tmp[3] = left[3]+right[3]+root->val;
            res = max(res,tmp[3]);

        }
        else{
            tmp[0]=0;
        }
        return tmp;
    }
};
// @lc code=end

