#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <sstream>
using namespace std;
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int res=-1;
        bool flag=true;
        for(int i=0;i<strs.size();i++){
            for(int j=0;j<strs.size();j++){
                // cout<<i<<" "<<j<<endl;
                if(i==j) continue;
                if(issubstr(strs[i],strs[j])) {
                    cout<<i<<"是"<<j<<"的子序列"<<endl;
                    flag = false;
                    break;//
                }
                
            }
            
            if(flag){
                cout<<i<<"成功晋级"<<endl;
                int l = strs[i].size();
                res = max(res,l);
                
            }
            flag = true;            
        }
        return res;
    }
    bool issubstr(string &a, string & b){
        //a是b的子序列吗？
        int i=0,j=0;
        while(i<a.size()&&j<b.size()){
            if(a[i]==b[j]) {
                i++;
                j++;
            }
            else j++;
        }
        if(i<a.size()) return false;
        // if(i==a.size()&&j<=b.size()) return true;
        return true;
    }
};

int main(){
    string input;
    getline(cin,input);
    stringstream ii;
    string tmp;
    ii<<input;
    vector<string> strs;
    Solution s;
    while(ii>>tmp){
        strs.emplace_back(tmp);
    }
    cout<<s.findLUSlength(strs)<<endl;

}