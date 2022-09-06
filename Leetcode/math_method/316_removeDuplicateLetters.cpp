#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
#include <string.h>
using namespace std;
class Solution {
public:
    string removeDuplicateLetters(string s) {
        stack<char> st;
        int visit[26];
        int count[26];
        memset(visit,0,sizeof(visit));
        memset(count,0,sizeof(count));
        for(char& c:s){
            ++count[c-'a'];
        }

        for(int i=0;i<s.size();i++){
            char c = s[i];
            --count[c-'a'];//要放在外面

            if(visit[c-'a']==1) {//访问过的就不做任何操作，因为贪心保证字典序最小
                continue;
            }

            while(!st.empty()&& c<st.top() ){
                //想要弹出,但是
                if(count[st.top()-'a']>0){
                    visit[st.top()-'a']=0;
                    st.pop();
                }
                else{
                    break;//不然不给弹出
                }

            }
            visit[c-'a']=1;
            st.push(c);
            
            
        }
    string res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(),res.end());
    return res;

    }
};


int main(){
    Solution s;
    cout<<s.removeDuplicateLetters("bcabc");
    return 0;
}