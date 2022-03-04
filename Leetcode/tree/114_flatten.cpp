#include "TreeNode.h"

class Solution {
public:
    void flatten(TreeNode* root) {
        //先不考虑什么时候停止
        if(root==nullptr){
            return;
        }
        
        //再不考虑什么时候遍历
        flatten(root->left);
        flatten(root->right);

        //先把操作逻辑写出来
        //我有一个根，我要把左节点接到自己的右边上
        TreeNode *left = root->left;
        TreeNode *right = root->right;

        root->left = nullptr;
        root->right = left;

        //循环遍历到链表尾端,不能改变头节点root
        TreeNode *p = root;
        while(p->right!=nullptr){
            p=p->right;
        }
        p->right = right;


    }

    
};