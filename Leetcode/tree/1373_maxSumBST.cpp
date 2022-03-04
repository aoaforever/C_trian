#include "TreeNode.h"
#include <vector>
#include <limits.h>
#include <iostream>

using namespace std;
class Solution {
public:
    int maxSumBST(TreeNode* root) {
        preorder_traverse(root);
        return maxNum;
    }
public:
    int maxNum=0;
    //[1:是BST，最小值， 最大值， 节点和]
    vector<int> traverse(TreeNode* root){
        if(root==NULL){
            return vector<int>{1,INT_MAX,INT_MIN,0};
        }

        vector<int> left = traverse(root->left);
        vector<int> right = traverse(root->right);

        //获取左子树的最大值，右子树的最小值，和左右子树各自的节点和
        //以当前节点为根的节点和
        vector<int> res;
        if(left[0]==1&&right[0]==1&&root->val>left[2]&&root->val<right[1]){
            //那么以当前为根 的也是BST
            res.push_back(1);
            //当前的最小值
            res.push_back(min(left[1],root->val));
            //当前的最大值
            res.push_back(max(right[2],root->val));
            //当前的节点和
            res.push_back(root->val+left[3]+right[3]);
            //更新BST最大节点和
            maxNum = max(res[3],maxNum);
        }
        else{
            res.push_back(0);
        }
        return res;
    }

    int findMin(TreeNode* root){//是右子树的最小值，是右子树的最左边
        if(root==NULL){
            return INT_MAX;
        }

        //前序遍历？其实无所谓,这里用后续遍历咯
        int left= findMin(root->left);
        int right= findMin(root->right);
        
        return min(min(root->val,left),right);

    }

    int findMax(TreeNode* root){//是左子树的最大值，是左子树的最右边
        if(root==NULL){
            return INT_MIN;
        }

        //前序遍历？其实无所谓,这里用后续遍历咯
        int left= findMax(root->left);
        int right= findMax(root->right);
        
        return max(max(root->val,left),right);

    }

    bool isBST(TreeNode* root,TreeNode* min, TreeNode* max){//前序遍历，需要辅助变量
        if(root==NULL){
            return true;
        }
        //前序遍历，先验证当前是否比左大，比又小。然后往后递归
        if(max!=NULL && root->val >= max->val){
            return false;
        }

        if(min!=NULL && root->val <= min->val){
            return false;
        }

        return isBST(root->left,min,root)
                && isBST(root->right,root,max);//root>root->left>min
                                               //max > root->right > root

        
    }
    int findSum(TreeNode* root){
        if(root==NULL){
            return 0;
        }
        int left = findSum(root->left);
        int right = findSum(root->right);
        return root->val+left+right;
    }

    void preorder_traverse(TreeNode* root){
        if(root==NULL){
            return;
        }
        //左右是否为BST
        if(!isBST(root->left,NULL,NULL)||!isBST(root->right,NULL,NULL)){
            //只要其中一个不是BST，那么当前肯定不是BST
            //问题出在这里
            //假如第一个gen的左右都不是BST，应该往下搜
            // return;

            preorder_traverse(root->left);
            preorder_traverse(root->right);
            
        }
        //如果左右都是，那就判断当前是不是
        int left = findMax(root->left);
        int right = findMin(root->right);

        //如果当前是,那么更新节点和
        int leftsum = findSum(root->left);
        int rightsum = findSum(root->right);
        int rootSum = leftsum + rightsum + root->val;      
        if(root->val <= left || root->val >= right){
            //如果当前不是，但是左右都是，只需要看左右谁更大？
            // return;//这里也错了，因该递归下去
            // preorder_traverse(root->left);
            // preorder_traverse(root->right);
            maxNum = max(max(leftsum,rightsum),maxNum);

        }  
        else 
            maxNum = max(maxNum,rootSum);


        // preorder_traverse(root->left);
        // preorder_traverse(root->right);
    }
};

int main(){
    /*
                    5
                3       7
            1      4  6     8
    
    */

    /*
                    4
                3       2
            n      1
    
    */
    TreeNode* t = new TreeNode();
    t->val = 4;
    t->left = new TreeNode(3);
    // t->left->left = new TreeNode(1);
    t->left->right = new TreeNode(1);

    t->right = new TreeNode(2);
    // t->right->left = new TreeNode(6);
    // t->right->right = new TreeNode(8);
    Solution s;
    cout<<s.maxSumBST(t);
    return 0;
}