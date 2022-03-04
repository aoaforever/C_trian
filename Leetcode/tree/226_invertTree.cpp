#include "TreeNode.h"

class Solution {

public:
    TreeNode* invertTree(TreeNode* root) {
        //后序翻转,先序也可以,不能交换值,只能交换指针

        if(root==nullptr){
            return nullptr;
        }
        invertTree(root->left);
        invertTree(root->right);

        // int tmp = root->left->val;
        // root->left->val = root->right->val;
        // root->right->val = tmp;

        TreeNode* tmp=root->right;
        root->right = root->left;
        root->left = tmp;
        tmp=nullptr;
        
        
        return root;
    }
};