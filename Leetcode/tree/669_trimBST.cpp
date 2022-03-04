#include "TreeNode.h"
#include <cstdio>
using namespace std;
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == NULL) {
            return NULL;
        }
        if (root->val < low) {
            //因为是二叉搜索树,节点.left < 节点 < 节点.right
            //节点数字比low小,就把左节点全部裁掉.
            root = root->right;
            //裁掉之后,继续看右节点的剪裁情况.剪裁后重新赋值给root.
            root = trimBST(root, low, high);
        } else if (root->val > high) {
            //如果数字比high大,就把右节点全部裁掉.
            root = root->left;
            //裁掉之后,继续看左节点的剪裁情况
            root = trimBST(root, low, high);
        } else {
            //如果数字在区间内,就去裁剪左右子节点.
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
        }
        return root;
    }


};


//通过后续遍历也能求解。但这抛弃了BST的性质。
TreeNode* digui(TreeNode* root,int low, int high){
    if(root==NULL){
        return NULL;
    }

    root->left = digui(root->left,low,high);
    root->right = digui(root->right,low,high);

    //当前节点
    if(root->val<low){
        return root->right;
    }
    else if(root->val>high){
        return root->left;
    }
    return root;
}