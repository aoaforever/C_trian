#include "TreeNode.h"
#include<vector>
#include<limits.h>
using namespace std;

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums,0,nums.size()-1);
    }
private:
    TreeNode* build(vector<int>& nums, int lo, int hi){
        //退出条件
        if(lo>hi){
            return NULL;
        }

        //逻辑
        //找出最大值
        int index =-1, maxVal = INT_MIN;
        for(int i=lo;i<=hi;i++){
            if(nums[i]>maxVal){
                maxVal = nums[i];
                index = i;
            }
        }

        TreeNode* root =new TreeNode(maxVal);
        root->left = build(nums,lo,index-1);
        root->right = build(nums,index+1,hi);
        return root;
    }
};