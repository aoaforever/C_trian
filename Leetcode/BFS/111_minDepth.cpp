#include <iostream>
#include "TreeNode.h"
#include <queue>
using namespace std;

class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int depth=1;

        while (!q.empty())
        {
            int sz = q.size();//注意一定要在外面取容量，而不是在for循环中，因为for循环会更新q的size，导致无法更新深度。
            //从左到右问候一遍，并且向队列添加孩子
            for(int i=0;i<sz;i++){
                TreeNode* node = q.front();
                q.pop();

                //判断是否达标
                if(node->left==NULL&&node->right==NULL){
                    return depth;
                }

                if(node->left!=NULL){
                    q.push(node->left);
                }
                if(node->right!= NULL){
                    q.push(node->right);
                }
            }
            //添加完之后，深度加一，进入下一层
            depth++;
        }
        return depth;
    }
};