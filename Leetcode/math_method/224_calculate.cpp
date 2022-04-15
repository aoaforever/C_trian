#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;
class Solution {
public:
    int calculate(string s) {
        return helper(s)[0];
    }
    vector<int> helper(string s){
        // cout<<s<<endl;;
        int num=0;
        stack<int> stk;
        char sign='+';
        int i=0;
        for(;i<s.size();i++){
            char c = s[i];
            //当前字符就四个情况，要么是整数，要么是符号,要么是括号，要么是空格
            if(isdigit(c)){
                num = num*10 +(c-'0');
            }
            if(c=='(') {
                vector<int> a = helper(s.substr(i+1));
                num = a[0];
                i = i+ a[1];
            }
            if((!isdigit(c)&&c!=' ')||i==s.size()-1){//如果c不是整数，有可能是符号和空格，要排除空格
            //如果i在最后，那么一定有sign和num
                switch(sign){//注意是switch之前的符号
                    case '+':
                        stk.push(num);
                        break;
                    case '-':
                        stk.push(-num);
                        break;
                }
                num =0;
                sign = c;
            }
            if(c==')') break;//如果是右括号，这层递归就不要继续for循环了，
        }
        int res=0;
        while(!stk.empty()){
            res += stk.top();
            stk.pop();
        }
        // cout<<"   res: "<<res<<endl;
        return {res,i+1};
    }
    // void s_to_int(string s){
    //     //将s转换为整数,不用stl
    //     int nums=0;
    //     for(int i=0;i<s.size();i++){
    //         if(isdigit(s[i])){
    //             num = num*10 + (s[i]-'0');
    //         }
    //     }
    // }
};