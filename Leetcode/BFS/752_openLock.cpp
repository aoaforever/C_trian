#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

/*
输入：
["8888"]
"0009"
输出：
9
预期结果：
1
*/
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<string> q;
        q.push("0000");
        int step=0;
        set<string> used;
        used.insert("0000");
        while (!q.empty())
        {
            int sz = q.size();
            for(int i=0;i<sz;i++){
                string s = q.front();
                q.pop();

                //退出条件
                if(s==target){
                    return step;
                }
                if(isIndeadends(deadends,s)){
                    continue;//如果存在于deadends，就跳过这个string。
                }

                //二话不说先写添加节点的东西
                //有四位，每次只能修改一位，因此不同的位修改表示不同的节点。
                //一位的修改有两种情况，加或减
                for(int j=0;j<4;j++){//一共有四位
                    //两种情况
                    string up = plusone(s,j);
                    string down = minusone(s,j);
                    if(used.find(up)==used.end()){
                        q.push(up);
                        used.insert(up);
                    }
                    if(used.find(down)==used.end()){
                        q.push(down);
                        used.insert(down);
                    }
                }
            }
            step++;
        }
        return step;        
    }
    bool isIndeadends(vector<string>& deadends,const string& s){
        for(auto& ss:deadends){
            if(ss==s){
                return true;
            }
        }
        return false;
    }
    string plusone(string s, int j){
        if(s[j]=='9'){
            s[j]='0';
        }
        else s[j]++;
        return s;
    }
    string minusone(string s, int j){
        if(s[j]=='0'){
            s[j]='9';
        }
        else s[j]--;
        cout<<s;
        return s;
    }
};


int main(){
    string a = "0000";
    Solution asd;
    string ss = asd.minusone(a,3);
    cout<<a<<endl;
    cout<<ss;
    return 0;
}