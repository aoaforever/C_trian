/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 *
 * https://leetcode-cn.com/problems/validate-binary-search-tree/description/
 *
 * algorithms
 * Medium (35.92%)
 * Likes:    1564
 * Dislikes: 0
 * Total Accepted:    500.5K
 * Total Submissions: 1.4M
 * Testcase Example:  '[2,1,3]'
 *
 * 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
 * 
 * 有效 二叉搜索树定义如下：
 * 
 * 
 * 节点的左子树只包含 小于 当前节点的数。
 * 节点的右子树只包含 大于 当前节点的数。
 * 所有左子树和右子树自身必须也是二叉搜索树。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：root = [2,1,3]
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [5,1,4,null,null,3,6]
 * 输出：false
 * 解释：根节点的值是 5 ，但是右子节点的值是 4 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点数目范围在[1, 10^4] 内
 * -2^31 <= Node.val <= 2^31 - 1
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
// class Solution {
// public:
//     bool isbst;
//     bool isValidBST(TreeNode* root) {
//         return judge(root,nullptr,nullptr);
//     }
//     bool judge(TreeNode* root,TreeNode* min,TreeNode* max){
//         if(root==nullptr) return true;
//         if(min!=NULL&&root->val <= min->val) return false;
//         if(max!=NULL&&root->val >= max->val )return false;
//         return judge(root->left,min,root)&&judge(root->right,root,max);
//     }
// };

class Solution {
public:
    long pre=LONG_MIN;
    bool isValidBST(TreeNode* root) {
        cout<<pre<<endl;

        return judge(root);
    }
    bool judge(TreeNode* root){
        if(root == nullptr) return true;
        bool left = judge(root->left);
        if(root->val<=pre) return false;
        pre= root->val;
        bool right = judge(root->right);
        return left&&right;
    }
};
// @lc code=end

