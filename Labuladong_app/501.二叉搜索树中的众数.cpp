/*
 * @lc app=leetcode.cn id=501 lang=cpp
 *
 * [501] 二叉搜索树中的众数
 *
 * https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/description/
 *
 * algorithms
 * Easy (52.95%)
 * Likes:    451
 * Dislikes: 0
 * Total Accepted:    97.1K
 * Total Submissions: 182.9K
 * Testcase Example:  '[1,null,2,2]'
 *
 * 给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。
 * 
 * 如果树中有不止一个众数，可以按 任意顺序 返回。
 * 
 * 假定 BST 满足如下定义：
 * 
 * 
 * 结点左子树中所含节点的值 小于等于 当前节点的值
 * 结点右子树中所含节点的值 大于等于 当前节点的值
 * 左子树和右子树都是二叉搜索树
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [1,null,2,2]
 * 输出：[2]
 * 
 * 
 * 示例 2：
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
 * 树中节点的数目在范围 [1, 10^4] 内
 * -10^5 <= Node.val <= 10^5
 * 
 * 
 * 
 * 
 * 进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）
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
    int cur_count ;
    int max_count ;
    TreeNode* prev;
    vector<int> res;
    vector<int> findMode(TreeNode* root) {
        dfs(root);
        prev = nullptr;
        vector<int> r;
        cout<<res.size();
        for(auto& s:res){
            r.push_back(s);
        }
        return r;

    }
    void dfs(TreeNode* root){
        if(root==NULL) return;
        dfs(root->left);
        //中序遍历的位置,BST能够变成有序数组
        if(prev==NULL){
            //初始化
            cur_count =1;
            max_count =1;
            res.push_back(root->val);
        }
        else{
            if(prev->val == root->val){
                cur_count++;
                if(cur_count>max_count){
                    max_count = cur_count;
                    res.clear();
                    cout<<"clear "<<res.size();
                    res.push_back(root->val);
                }
                else if(cur_count==max_count){
                    res.push_back(root->val);
                }
            }
            if(prev->val != root->val){
                cur_count =1;
                if(cur_count==max_count){
                    res.push_back(root->val);
                }
            }
        }
        prev = root;
        dfs(root->right);
        
    }
};
// @lc code=end

