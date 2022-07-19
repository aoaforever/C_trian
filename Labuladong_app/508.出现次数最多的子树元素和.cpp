/*
 * @lc app=leetcode.cn id=508 lang=cpp
 *
 * [508] 出现次数最多的子树元素和
 *
 * https://leetcode.cn/problems/most-frequent-subtree-sum/description/
 *
 * algorithms
 * Medium (75.30%)
 * Likes:    196
 * Dislikes: 0
 * Total Accepted:    37.3K
 * Total Submissions: 49.6K
 * Testcase Example:  '[5,2,-3]'
 *
 * 给你一个二叉树的根结点 root ，请返回出现次数最多的子树元素和。如果有多个元素出现的次数相同，返回所有出现次数最多的子树元素和（不限顺序）。
 * 
 * 一个结点的 「子树元素和」 定义为以该结点为根的二叉树上所有结点的元素之和（包括结点本身）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入: root = [5,2,-3]
 * 输出: [2,-3,4]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入: root = [5,2,-5]
 * 输出: [2]
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 节点数在 [1, 10^4] 范围内
 * -10^5 <= Node.val <= 10^5
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
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res;
        dfs(root);
        for(auto mm:m){
            // cout<<mm.first<<endl;
            if(mm.second==max_freq){
                res.emplace_back(mm.first);
            }
        }
        return res;
    }
    unordered_map<int,int> m;
    int max_freq=0;
    int dfs(TreeNode* root){
        if(root==NULL){
            return 0;
        }
        int left = dfs(root->left);
        int right = dfs(root->right);

        int sum = root->val + left+right;
        m[sum]++;
        max_freq = max(max_freq,m[sum]);
        return sum;
    }
};
// @lc code=end

