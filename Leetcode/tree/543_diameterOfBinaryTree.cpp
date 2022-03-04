#include "TreeNode.h"

using namespace std;
//细节，主函数return谁
// 递归函数return谁，深度
class Solution {
public:
    int maxdiameter =0;
    int diameterOfBinaryTree(TreeNode* root) {
        maxdepth(root);
        return maxdiameter;
    }
    
    int maxdepth(TreeNode* root){
        if(root==NULL) return 0;
        int left = maxdepth(root->left);
        int right = maxdepth(root->right);
        int mydia = left+right;
        //当前最大直径就是
        maxdiameter =max(maxdiameter,mydia);

        return max(left,right)+1;
    }
};