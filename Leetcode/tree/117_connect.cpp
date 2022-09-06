// package com.leetcode.explore.learnCard.dataStructureBinaryTree.conclusion4;

/*
117. 填充每个节点的下一个右侧节点指针 II
给定一个二叉树

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

 

进阶：

你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
 

示例：

/**/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

/*这次和116相比，117不是完全二叉树*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root==NULL) return NULL;
        if(root->left&& root->right){
            root->left->next = root->right;
            root->right->next = getnext(root);
        }
        else if(root->left){
            root->left->next = getnext(root);
        }
        else if(root->right){
            root->right->next = getnext(root);
        }

        connect(root->right);
        connect(root->left);

        return root;
    }
    Node* getnext(Node* root){

        while(root->next){
            if(root->next->left){
                return root->next->left;
            }
            if(root->next->right){
                return root->next->right;
            }
            root = root->next;
        }
        return NULL;
    }
};


/**
 * 补充节点的右侧指针，不是完美二叉树
 */
public class Solution {
    public Node connect(Node root) {
        if (root == null || (root.right == null && root.left == null)) {
            return root;
        }
        if (root.left != null && root.right != null) {
            root.left.next = root.right;
            root.right.next = getNextNoNullChild(root);
        }
        if (root.left == null) {
            root.right.next = getNextNoNullChild(root);
        }
        if (root.right == null) {
            root.left.next = getNextNoNullChild(root);
        }

        //这里要注意：先递归右子树，否则右子树根节点next关系没建立好，左子树到右子树子节点无法正确挂载
        root.right = connect(root.right);
        root.left = connect(root.left);

        return root;
    }

    /**
     * 一路向右找到有子节点的根节点
     */
    private static Node getNextNoNullChild(Node root) {
        while (root.next != null) {
            if (root.next.left != null) {
                return root.next.left;
            }
            if (root.next.right != null) {
                return root.next.right;
            }
            root = root.next;
        }
        return null;
    }
}

