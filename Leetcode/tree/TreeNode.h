#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//二叉树的最大深度
int maxDepth(TreeNode* root){

    if (root==nullptr){
        return 0;
    }
    //先知道左右子树的最大深度
    int  left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return max(left,right)+1;
}


    // TreeNode* t = new TreeNode();
    // t->val = 5;
    // t->left = new TreeNode(3);
    // t->left->left = new TreeNode(1);
    // t->left->right = new TreeNode(4);

    // t->right = new TreeNode(7);
    // t->right->left = new TreeNode(6);
    // t->right->right = new TreeNode(8);
