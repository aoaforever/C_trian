#include <limits.h>
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

class Solution{
private:
    int ans = INT_MIN;
public:
    int maxPathSum(TreeNode* root){
        

        dfs(root);
        return ans;
    }

    int dfs(TreeNode* root){
        if(root==nullptr){
            return 0;
        }

        int left = max(0,dfs(root->left));
        int right = max(0,dfs(root->right));
        ans = max(ans, left+right+root->val);
        return max(left,right)+root->val;
    }

};
//第二次解，还是有细节，递归return谁？，路径和<0的处理、
class Solution {
public:
    int maxsum =INT_MIN;
    int maxPathSum(TreeNode* root) {
        digui(root);
        return maxsum;
    }
    int digui(TreeNode* root){
        if(root==NULL) return 0;
        //2.如果左右子树的路径和<0,要抛弃掉
        int left = max(0,digui(root->left));
        int right = max(0,digui(root->right));
        //这里更新最大路径和
        maxsum =max(maxsum,left+right+root->val);
        //因为只能走一条边啊，所以应该返回max(左子树路径和,右子树路径和)+当前节点
        return max(left,right)+root->val; 
    }
};