#include "TreeNode.h"
#include <string>
#include <list>
#include <iostream>
#include <sstream>
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

    string  s ="1,-2,#,4,#,#,3,#,#";
    // Codec c;
    // c.deserialize(s);


    stringstream ss;
    ss<<s;
    list<string> l;
    string asd;
    while(getline(ss,asd,',')){
        l.push_back(asd);
        cout<<asd<<endl;
        asd.clear();
    }
    cout<<l.size();
    return 0;
}

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==NULL) return "#";
        
        string left = serialize(root->left);
        string right = serialize(root->right);

        //通过后序遍历，子问题来得到解
        string res;
        res += to_string(root->val)+","+left+","+right;
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        list<string> l;
        string tmp;
        for(char& d:data){
            if(d==','){
                l.push_back(tmp);
                tmp.clear();
            }
            else {
                tmp.push_back(d);
            }
        }
        return deser(l);
    }
    TreeNode* deser(list<string>& data){
        if(data.empty()) return NULL;
        string d = data.front();
        data.pop_front();

        if(d=="#") return NULL;


        TreeNode* root = new TreeNode(stoi(d));
        root->left = deser(data);
        root->right = deser(data);
        

        return root;
    }
};



//后序遍历 getline,stringstream
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==NULL) return "#";
        
        string left = serialize(root->left);
        string right = serialize(root->right);

        //通过后序遍历，子问题来得到解
        string res;
        res += left+","+right+","+to_string(root->val);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
        cout<<data<<endl;
        list<string> l;
        string tmp;
        stringstream ss;
        ss<<data;
        while(getline(ss,tmp,',')){
            l.push_back(tmp);
            tmp.clear();
        }

        // for(char& d:data){
        //     if(d==','){
        //         l.push_back(tmp);
        //         tmp.clear();
        //     }
        //     else {
        //         tmp.push_back(d);
        //     }
        // }
        cout<<l.size()<<endl;
        return deser(l);
    }
    TreeNode* deser(list<string>& data){
        if(data.empty()) return NULL;
        string d = data.back();
        // cout<<data.size()<<" ";
        data.pop_back();

        if(d=="#") return NULL;


        TreeNode* root = new TreeNode(stoi(d));
        root->right = deser(data);
        root->left = deser(data);
        
        

        return root;
    }
};