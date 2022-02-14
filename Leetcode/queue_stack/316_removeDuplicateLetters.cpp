#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>

//s 由小写英文字母组成
using namespace std;

class Solution {
public:
    // //第一步：只需要不重复就好，
    // string removeDuplicateLetters(string s) {
    //     stack<char> stk;
    //     vector<int> inStack(26,0);

    //     for(char c :s){
    //         //如果字符c存在栈中，直接跳过
    //         if(inStack[c-'a'] != 0){
    //             continue;
    //         }
    //         //若不存在，则插入栈顶并标记为存在
    //         stk.push(c);
    //         inStack[c-'a']++;
    //     }

    //     string res;
        
    //     while(!stk.empty()){
    //         res += stk.top() ;
    //         stk.pop();
    //     }

    //     //栈中元素插入顺序是反的，需要reverse一下
    //     reverse(res.begin(),res.end());
    //     return res;
    // }

    // //第二步
    // string removeDuplicateLetters(string s) {
    //     stack<char> stk;
    //     vector<int> inStack(26,0);

    //     for(char c :s){
    //         //如果字符c存在栈中，直接跳过
    //         if(inStack[c-'a'] != 0){
    //             continue;
    //         }

    //         //插入之前，和之前的元素比较一下大小
    //         //如果字典序比前面的小，pop前面的元素
    //         while(!stk.empty() && stk.top() > c){
    //             //弹出栈顶元素，并把该元素标记为不在栈中
    //             inStack[stk.top()-'a']--;
    //             stk.pop();
    //         }
            
    //         //若不存在，则插入栈顶并标记为存在
    //         stk.push(c);
    //         inStack[c-'a']++;
    //     }

    //     string res;
        
    //     while(!stk.empty()){
    //         res += stk.top() ;
    //         stk.pop();
    //     }

    //     //栈中元素插入顺序是反的，需要reverse一下
    //     reverse(res.begin(),res.end());
    //     return res;
    // }

    //第三步：如何让算法之道字符'a'之后有几个'b'有几个'c'呢？
    string removeDuplicateLetters(string s) {
        stack<char> stk;
        vector<int> inStack(26,0);
        vector<int> count(26,0);

        for(char c:s){
            count[c-'a']++;
        }

        for(char c :s){
            //每遍历过一个字符，都将对应的计数减一
            count[c-'a']--;

            //如果字符c存在栈中，直接跳过
            if(inStack[c-'a'] != 0){
                continue;
            }

            //插入之前，和之前的元素比较一下大小
            //如果字典序比前面的小，pop前面的元素
            while(!stk.empty() && stk.top() > c){
                //若之后不存在栈顶元素了，则停止pop
                if(count[stk.top()-'a'] ==0 ){
                    break;
                }
                //若之后还有，则可以pop
                //弹出栈顶元素，并把该元素标记为不在栈中
                inStack[stk.top()-'a']--;
                stk.pop();
            }
            
            //若不存在，则插入栈顶并标记为存在
            stk.push(c);
            inStack[c-'a']++;
        }

        string res;
        
        while(!stk.empty()){
            res += stk.top() ;
            stk.pop();
        }

        //栈中元素插入顺序是反的，需要reverse一下
        reverse(res.begin(),res.end());
        return res;
    }
};


int main(){
    Solution s;
    string a="bcac";
    string c = s.removeDuplicateLetters(a);
    // cout<<a<<endl;
    cout<<c<<endl;
}