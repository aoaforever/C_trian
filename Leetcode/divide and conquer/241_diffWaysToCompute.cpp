#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        //选择：从左到右的所有运算符
        vector<int> res;
        for(int i=0;i<expression.size();i++){
            char c = expression[i];
            if(c=='-'||c=='+'||c=='*'){
                //那么就可以做括号处理。
                vector<int> left = diffWaysToCompute(expression.substr(0,i));
                vector<int> right = diffWaysToCompute(expression.substr(i+1));
                //这两个子问题返回了所有可能的结果，因此对这些结果进行c运算符。
                for(int l:left){
                    for(int r:right){
                        if(c=='-'){
                            res.push_back(l-r);
                        }
                        else if(c=='+'){
                            res.push_back(l+r);
                        }
                        else if(c=='*'){
                            res.push_back(l*r);
                        }
                    }
                }
            }
            //没匹配到运算符，啥都不干
        }
        //base case 是如果res为空，那么string是只有一个数字没有运算符
        if(res.empty()){
            res.push_back(atoi(expression.c_str()));
        }
        
        return res;
    }
};