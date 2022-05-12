/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
 *
 * https://leetcode-cn.com/problems/diameter-of-binary-tree/description/
 *
 * algorithms
 * Easy (56.72%)
 * Likes:    1018
 * Dislikes: 0
 * Total Accepted:    214.4K
 * Total Submissions: 377K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
 * 
 * 
 * 
 * 示例 :
 * 给定二叉树
 * 
 * ⁠         1
 * ⁠        / \
 * ⁠       2   3
 * ⁠      / \     
 * ⁠     4   5    
 * 
 * 
 * 返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。
 * 
 * 
 * 
 * 注意：两结点之间的路径长度是以它们之间边的数目表示。
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
    int res=-1;
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return res;

    }
    int dfs(TreeNode* root){
        if(root==NULL) return 0;
        
        int left = dfs(root->left);
        int right = dfs(root->right);
        // cout<<root->val<<endl;
        //获得了左右节点的最深路劲,树的高度
        int length = left+right+1-1;//结点数-1=边数
        // cout<<"length:"<<length<<endl;
        res = max(res,length);
        // cout<<"res:"<<res<<endl;
        return max(left,right)+1;//返回树的高度
    }
};
// @lc code=end

