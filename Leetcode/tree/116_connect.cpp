#include <iostream>
using namespace std;
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

class Solution {
public:

    Node* connect(Node* root) {
        if(root==NULL){//加这个啊！！！！！！！！！！！！！不然又指针错误了
            return NULL;
        }
        connectTwoNode(root->left,root->right);
        return root;
    }
private:
    void connectTwoNode(Node * node1, Node* node2){
        //什么时候停止
        if(node1==NULL||node2==NULL){
            return;
        }

        node1->next = node2;
        //连接node1的子节点
        connectTwoNode(node1->left,node1->right);
        //连接node2的子节点
        connectTwoNode(node2->left,node2->right);
        //连接不同父节点的子节点
        connectTwoNode(node1->right,node2->left);
    }
};