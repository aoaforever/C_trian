#include <string>
#include <stack>

using namespace std;

char leftof( char c){//也可以用哈希表实现键值配队
    if (c=='}') return '{';
    else if (c == ')') return '(';
    return '[';

}

bool isValid(string s){
    stack<char> left;
    for(char c :s){
        if(c=='[' || c=='{' || c=='('){
            //左括号就入栈
            left.push(c);
        }
        else{
            //右括号出栈
            if(!left.empty() && leftof(c)==left.top() ){
                left.pop();
            }
            else {//和最近的左括号不匹配
                return false;
            }
        }
    }
    return left.empty();
}