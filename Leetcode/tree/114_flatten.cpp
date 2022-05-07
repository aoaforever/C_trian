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

//二刷，没想到需要遍历到最后才能接上原来的right
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==NULL) return ;
        flatten(root->left);
        flatten(root->right);
        if(root->left==NULL&&root->right==NULL) return ;//叶子节点直接return
        //两个节点都在
        if(root->left&&root->right){

            TreeNode* tmp = root->right;
            // root->left->right = tmp;
            root->right = root->left;
            root->left = NULL;
            TreeNode* n=root;
            while(n->right!=NULL){
                n=n->right;
            }
            n->right = tmp;
        }
        //只有左节点
        else if(root->left&&root->right==NULL){
            root->right= root->left;
            root->left = NULL;
        }
        //只有右节点
        else if(root->right&&root->left==NULL){
            return;
        }

    }
};