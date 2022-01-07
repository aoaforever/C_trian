#include <unordered_map>
#include <vector>
using namespace std;


 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*对于任意一颗树而言，前序遍历的形式总是
[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]

即根节点总是前序遍历中的第一个节点。而中序遍历的形式总是
[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/cong-qian-xu-yu-zhong-xu-bian-li-xu-lie-gou-zao-9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
class Solution{
private:
    unordered_map<int,int> index;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
        int n =preorder.size();

        //构造哈希映射，帮助我们快速定位根节点
        for(int i=0;i<n;i++){
            index[inorder[i]] = i;//键是遍历值，值是位置
        }

        TreeNode* root =myBuildTree(preorder,inorder,0,n-1,0,n-1);
        return root;

    }

    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left,int preorder_right,int inorder_left,int inorder_right){
        if(preorder_left>preorder_right){
            return nullptr;
        }

        //前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;//下标位置
        int inorder_root = index[preorder[preorder_root]];

        //先拔根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);
        //得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;//不加一？

        //递归的构造左子树，并连接到根节点
        //线序遍历中[从 左边界+1 开始的size_left_subtree]个元素就对应了中序遍历
        //[从 左边界 开始到根节点定位-1]的元素
        root->left = myBuildTree(preorder,inorder,preorder_left+1,preorder_left+size_left_subtree,inorder_left,inorder_root-1);

        //递归地构造右子树，并连接到根节点
        root->right = myBuildTree(preorder,inorder,preorder_left+size_left_subtree+1,preorder_right,inorder_root+1,inorder_right);
        return root;
    }
};