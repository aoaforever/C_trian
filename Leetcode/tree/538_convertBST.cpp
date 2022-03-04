#include "TreeNode.h"

//逆序输出，每次输出都是最大值，当前值肯定小于之前的值，累和就好
class Solution {
public:
    int sum = 0 ; 
     
    TreeNode* convertBST(TreeNode* root) {
        convertBST(root->right);
        sum+=root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};