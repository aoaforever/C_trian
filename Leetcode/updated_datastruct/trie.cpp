#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

//前缀树,特殊的count写法。叶子节点的count为0.
class TrieNode{
public:
    TrieNode(){
        count =0;
        children.resize(26,nullptr);
    }
    int count;
    // TrieNode* children[26];
    vector<TrieNode*> children;
};

class TrieTree{
public:
    TrieNode* head ;
    TrieTree(){
        head = new TrieNode();
    }

    TrieNode* insert(string& s){
        TrieNode* cur = head;
        for(int i=0;i<s.size();i++){
            int c = s[i]-'a';
            if(cur->children[c]==nullptr) cur->children[c] = new TrieNode();
            cur->count++;
            cur = cur->children[c];
        }
        return cur;//此时的cur的count是=0;
    }
};

//下面是例题 https://leetcode.cn/problems/short-encoding-of-words/submissions/
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        TrieTree* head = new TrieTree();//一个对象
        unordered_map<TrieNode*, int> nodes;//存前缀节点和单词下标的映射
        for(int i=0;i<words.size();i++){
            string tmp = words[i];
            reverse(tmp.begin(),tmp.end());
            TrieNode* node = head->insert(tmp);
            nodes[node] = i;
        }

        int res=0;
        for(auto& n:nodes){
            TrieNode* t = n.first;
            if(t->count==0){
                //是叶子节点
                res += words[n.second].size()+1;
            }
        }
        return res;
    }
    
class TrieNode{
public:
    TrieNode(){
        count =0;
        children.resize(26,nullptr);
    }
    int count;
    // TrieNode* children[26];
    vector<TrieNode*> children;
};

class TrieTree{
public:
    TrieNode* head ;
    TrieTree(){
        head = new TrieNode();
    }

    TrieNode* insert(string& s){
        TrieNode* cur = head;
        for(int i=0;i<s.size();i++){
            int c = s[i]-'a';
            if(cur->children[c]==nullptr) cur->children[c] = new TrieNode();
            cur->count++;
            cur = cur->children[c];
        }
        return cur;//此时的cur的count是=0;
    }
};
};

int main(int argc, char const *argv[])
{
    vector<string> words{"time","me","bell"};
    Solution s;
    s.minimumLengthEncoding(words);
    return 0;
}



/*
正常写法，val>0代表的是以次字母结尾有这个字符串
*/

class TrieTree{
public:
    class TrieNode{
    public:
        TrieNode(){
            val =0;
            children.resize(26,nullptr);
        }
        int val;
        // TrieNode* children[26];
        vector<TrieNode*> children;
    };

    TrieNode* head ;
    TrieTree(){
        head = new TrieNode();
    }

    void insert(string& s){
        TrieNode* cur = head;
        for(int i=0;i<s.size();i++){
            int c = s[i]-'a';
            if(cur->children[c]==nullptr) cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->val++;
    }

    bool search(string& s){
        //搜索s是否存在于这个前缀树中
        TrieNode* cur = head;
        for(char& c:s){
            if(cur->children[c-'a']==nullptr) return false;
            cur = cur->children[c-'a'];
        }
        if(cur->val==0) return false;//没有以某个单词结尾的前缀树,也就是这个字符串虽然满足前缀，但是不是完全相同
        return true;
    }
    


};

int main(int argc, char const *argv[])
{
    
    return 0;
}

string help(string input){
    string res;
    for(int i=0;i<input.size();i++){
        if(input[i]>='a'||input[i]<='z'){
            res.push_back(input[i]);
        }
    }
    return res;
}
