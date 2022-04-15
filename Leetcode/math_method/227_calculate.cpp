#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

//没有括号的计算器
class Solution {
public:
    int calculate(string s) {
        return helper(s);
    }
    int helper(string s){
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

            if((!isdigit(c)&&c!=' ')||i==s.size()-1){//如果c不是整数，有可能是符号和空格，要排除空格
            //如果i在最后，那么一定有sign和num
                switch(sign){//注意是switch之前的符号
                    int p;
                    case '+':
                        stk.push(num);
                        break;
                    case '-':
                        stk.push(-num);
                        break;
                    case '*':
                        p=stk.top();
                        stk.pop();
                        stk.push(p*num);
                        break;
                    case '/':
                        p=stk.top();
                        stk.pop();
                        stk.push(p/num);
                        break;

                }
                num =0;
                sign = c;
            }

        }
        int res=0;
        while(!stk.empty()){
            res += stk.top();
            stk.pop();
        }
        // cout<<"   res: "<<res<<endl;
        return res;
    }

};