#include "TreeNode.h"
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        find(root);
        return res;
    }
private:
    vector<TreeNode*> res;
    unordered_map<string,int> dup;
    string find(TreeNode* root){    
        //停止条件
        if(root==NULL){
            return "#";
        }

        string left = find(root->left);
        string right = find(root->right);
        string name = left + "," + right + "," + to_string(root->val);
        //如果存在这个子树，并且没有重复
        if(dup.count(name)){
            if (dup[name]==1){//必须等于1
                res.push_back(root);
                
            }
        }
        dup[name]++;
        return name;
    }
};