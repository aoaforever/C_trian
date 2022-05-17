/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
 *
 * https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (57.29%)
 * Likes:    629
 * Dislikes: 0
 * Total Accepted:    229.6K
 * Total Submissions: 400.7K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [3,9,20,null,null,15,7]
 * 输出：[[3],[20,9],[15,7]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [1]
 * 输出：[[1]]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：root = []
 * 输出：[]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点数目在范围 [0, 2000] 内
 * -100 <= Node.val <= 100
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
#include <vector>
#include<queue>
using namespace std;
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root==NULL) return vector<vector<int>>{};
        //层序遍历
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> res;
        bool flag =true;
        while(!q.empty()){
            int sz = q.size();
            deque<int> dq;
            for(int i=0;i<sz;i++){
                TreeNode* p = q.front();
                q.pop();
                if(flag){
                    dq.push_back(p->val);
                }
                else dq.push_front(p->val);
                
                
                if(p->left!=NULL){
                    q.push(p->left);
                }
                if(p->right!=NULL){
                    q.push(p->right);
                }
            }
            flag = !flag;
            res.emplace_back(vector<int>(dq.begin(),dq.end()));
        } 
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> s;
        if(root==NULL) return {};
        s.push(root);
        vector<vector<int>> res;
        bool flag =false;
        while (!s.empty())
        {
            int sz = s.size();
            vector<int> tmp;
            for(int i=0;i<sz;i++){
                TreeNode* q = s.front();
                s.pop();
                tmp.push_back(q->val);
                if(q->left) s.push(q->left);
                if(q->right) s.push(q->right);
            }
            if(flag) {
                reverse(tmp.begin(),tmp.end());
            }
            flag = !flag;
            res.push_back(tmp);
        }
        return res;
    }
};
// @lc code=end

