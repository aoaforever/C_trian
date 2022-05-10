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

class Solution {
public:
    int res=-1;
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return res;

    }
    int dfs(TreeNode* root){
        if(root==NULL) return 0;
        
        int left = dfs(root->left);
        int right = dfs(root->right);
        // cout<<root->val<<endl;
        //获得了左右节点的最深路劲,树的高度
        int length = left+right+1-1;//结点数-1=边数
        // cout<<"length:"<<length<<endl;
        res = max(res,length);
        // cout<<"res:"<<res<<endl;
        return max(left,right)+1;//返回树的高度
    }
};