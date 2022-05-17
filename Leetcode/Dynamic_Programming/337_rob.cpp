/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [337] 打家劫舍 III
 *
 * https://leetcode-cn.com/problems/house-robber-iii/description/
 *
 * algorithms
 * Medium (60.67%)
 * Likes:    1303
 * Dislikes: 0
 * Total Accepted:    184.8K
 * Total Submissions: 304.6K
 * Testcase Example:  '[3,2,3,null,3,null,1]'
 *
 * 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
 * 
 * 除了 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果
 * 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
 * 
 * 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 
 * 
 * 输入: root = [3,2,3,null,3,null,1]
 * 输出: 7 
 * 解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7
 * 
 * 示例 2:
 * 
 * 
 * 
 * 
 * 输入: root = [3,4,5,1,3,null,1]
 * 输出: 9
 * 解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 
 * 
 * 树的节点数在 [1, 10^4] 范围内
 * 0 <= Node.val <= 10^4
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
    unordered_map<TreeNode*,int> memo;
    int rob(TreeNode* root) {
        memo.clear();
        dp(root);
        return memo[root];
    }
    int dp(TreeNode* root){
        if(root==NULL) return 0;
        if(memo.count(root)) return memo[root];
        cout<<root<<endl;
        int do_it = root->val ;

        if(root->left) do_it += dp(root->left->left)+dp(root->left->right);
        if(root->right) do_it +=dp(root->right->left)+dp(root->right->right);
        int not_do =dp(root->left)+dp(root->right);
        memo[root] = max(do_it,not_do);      
        return memo[root];
    }
};


// class Solution {
// public:
//     vector<int> dfs(TreeNode* cur) {
//         if (cur == nullptr) return {0, 0};

//         vector<int> left = dfs(cur->left);
//         vector<int> right = dfs(cur->right);

//         vector<int> dp(2, 0);
//         dp[0] = max(left[0], left[1]) + max(right[0], right[1]);  // 当前结点不偷
//         dp[1] = cur->val + left[0] + right[0];                    // 当前结点偷了
//         return dp;
//     }
//     int rob(TreeNode* root) {
//         vector<int> res = dfs(root);
//         return max(res[0], res[1]);
//     }
// };


// @lc code=end

