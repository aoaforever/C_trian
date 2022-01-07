/*给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。

叶子节点 是指没有子节点的节点。

 */

#include <vector>
#include <string>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0),left(nullptr),right(nullptr){}
    TreeNode(int x): val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode* left, TreeNode* right): val(x),left(left),right(right){}
};

//这种写法会在叶子节点的时候不把值加进去就输出paths了。
class Solution{
public:
    vector<string> binaryTreePaths(TreeNode* root){
        vector<string> paths;
        //遍历一遍就完事了
        construct_paths(root,"",paths);
        return paths;
    }

    void construct_paths(TreeNode* root, string path, vector<string>& paths){
        if(root!=nullptr){
            //如果是叶子节点，将路径添加到paths里。
            if(root->left==nullptr&&root->right==nullptr){
                paths.push_back(path);
            }//如果不是叶子节点，则将当前节点追加到path里.
            else {
                path =path + to_string(root->val) + "->";
                construct_paths(root->left,path,paths);
                construct_paths(root->right,path,paths);
            }
        }
    }

};


//下面正确dfs
class Solution{
public:
    vector<string> binaryTreePaths(TreeNode* root){
        vector<string> paths;
        //遍历一遍就完事了
        construct_paths(root,"",paths);
        return paths;
    }

    void construct_paths(TreeNode* root, string path, vector<string>& paths){
        if(root!=nullptr){
            path += to_string(root->val);
            //如果是叶子节点，将路径添加到paths里。
            if(root->left==nullptr&&root->right==nullptr){
                paths.push_back(path);
            }//如果不是叶子节点，则将当前节点追加到path里.
            else {
                path += "->";
                construct_paths(root->left,path,paths);
                construct_paths(root->right,path,paths);
            }
        }
    }

};


//bfs
class Solution{
public:
    vector<string> binaryTreePaths(TreeNode* root){
        vector<string> paths;
        if(root==nullptr){
            return paths;
        }

        queue<TreeNode*> node_queue;
        queue<string> path_queue;

        node_queue.push(root);
        path_queue.push(to_string(root->val));

        //开始bfs模板
        while(!node_queue.empty()){
            //取出队列头节点，进行操作
            TreeNode* node = node_queue.front();
            node_queue.pop();

            string path = path_queue.front();
            path_queue.pop();

            //如果node是叶子节点，将路径放到paths里面。
            if (node->left==nullptr&&node->right==nullptr){
                paths.push_back(path);
            }
            else {
                if(node->left!=nullptr){
                    node_queue.push(node->left);
                    path_queue.push(path+"->"+to_string(node->left->val));
                }
                if(node->right!=nullptr){
                    node_queue.push(node->right);
                    path_queue.push(path+"->"+to_string(node->right->val));
                }
            }

            
        }

        return paths;
    }
};