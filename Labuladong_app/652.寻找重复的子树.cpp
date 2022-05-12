/*
 * @lc app=leetcode.cn id=652 lang=cpp
 *
 * [652] 寻找重复的子树
 *
 * https://leetcode-cn.com/problems/find-duplicate-subtrees/description/
 *
 * algorithms
 * Medium (57.88%)
 * Likes:    409
 * Dislikes: 0
 * Total Accepted:    49.6K
 * Total Submissions: 85.5K
 * Testcase Example:  '[1,2,3,4,null,2,4,null,null,4]'
 *
 * 给定一棵二叉树 root，返回所有重复的子树。
 * 
 * 对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。
 * 
 * 如果两棵树具有相同的结构和相同的结点值，则它们是重复的。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：root = [1,2,3,4,null,2,4,null,null,4]
 * 输出：[[2,4],[4]]
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：root = [2,1,1]
 * 输出：[[1]]
 * 
 * 示例 3：
 * 
 * 
 * 
 * 
 * 输入：root = [2,2,2,3,null,3,null]
 * 输出：[[2,3],[3]]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中的结点数在[1,10^4]范围内。
 * -200 <= Node.val <= 200
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
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<string,int> dup;
    vector<TreeNode*> res;
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return res;
    }
    string dfs(TreeNode* root){
        if(root==NULL) return "#";
        string left = dfs(root->left);
        string right = dfs(root->right);
        string now = to_string(root->val)+","+left+ "," + right;

        if(dup.count(now)&&dup[now]==1)  res.emplace_back(root);
        dup[now]++;
        // cout<<now<<endl;
        return now;
    }
};
// @lc code=end

