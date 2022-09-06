/*
https://leetcode.cn/problems/reverse-substrings-between-each-pair-of-parentheses/
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> st;
        vector<int> p(s.size());
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                st.push(i);
            }
            else if(s[i]==')'){
                int j = st.top();
                st.pop();
                p[i] = j;
                p[j] = i;
            }
        }

        string res;
        int step =1;
        int i=0;
        while(i<s.size()){
            if(s[i]=='('|| s[i]==')'){
                i = p[i];
                step = -step;
            }
            else {
                res.push_back(s[i]);
            }

            i += step;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    string t;
    while(getline(cin,t)){
        Solution s;
        cout<<s.reverseParentheses(t)<<endl;
    }

    return 0;
}
