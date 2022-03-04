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
class Solution {
public:

    vector<TreeNode*> generateTrees(int n) {

        return build(1,n);
    }
    vector<TreeNode*> build(int lo, int hi){
        vector<TreeNode*> res;
        if(lo>hi){ 
            //这里写错了。不知道返回什么。
            res.push_back(NULL);
            return res;
        }

        for(int i=lo;i<=hi;i++){
            vector<TreeNode*> left = build(lo,i-1);
            vector<TreeNode*> right = build(i+1,hi);
            for(auto l:left){
                for(auto r:right){
                    TreeNode* root = new TreeNode(i);//当前节点
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
            
        }
        
        return res;
    }
};