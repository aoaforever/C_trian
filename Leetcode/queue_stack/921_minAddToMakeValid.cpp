#include <string>

using namespace std;

class Solution{
public:
    int minAddToMakeValid(string s){
        //用一个need记录需要右括号
        int need =0;
        int res =0;
        for(int i =0; i<s.size(); i++){
            if(s[i]=='('){
                need++;
            }
            
            if(s[i]==')'){
                need--;
                if(need == -1){
                    //说明右括号多了，需要新的变量记录左括号
                    need =0;
                    res++;
                }
            }
        }
        return res+need;
    }
};