#include "TreeNode.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;
//没有考虑负数

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string sb;
        ser(root,sb);
        return sb;
    }

    // Decodes your encoded data to tree.
    //String data = "1,-2,#,4,#,#,3,#,#,";
    //String[] nodes = data.split(",");
    TreeNode* deserialize(string data) {
        list<string> dataArray;
        string s;
        for(auto& c: data){
            if(c==',') {
                dataArray.push_back(s);
                s.clear();
            }
            else s.push_back(c);
        }
        for(auto& l : dataArray){
            cout<<l<<" ";
        }
        return deser(dataArray);

    }
private:
    void ser(TreeNode* root,string &sb){
        if(root==NULL){
            sb = sb + "#" + ",";
            return ;
        }
        
        //前序遍历
        sb =sb + to_string(root->val)+",";

        ser(root->left,sb);
        ser(root->right,sb);
    }
    TreeNode* deser(list<string>& dataArray){
        if(dataArray.front() == "#") {
            // cout<<"yes"<<endl;
            dataArray.erase(dataArray.begin());
            return NULL;
        }

        string val = dataArray.front();
        dataArray.erase(dataArray.begin());

        if(val == "#") return NULL;
        // cout<<val<<endl;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deser(dataArray);
        root->right = deser(dataArray);
        return root;
    }
};

int main()
{

    string  s ="1,-2,#,4,#,#,3,#,#,";
    Codec c;
    c.deserialize(s);
    return 0;
}