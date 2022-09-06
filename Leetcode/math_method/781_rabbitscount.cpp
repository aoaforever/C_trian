#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.cn/problems/rabbits-in-forest/solution/tu-jie-si-lu-zi-dian-de-ying-yong-huo-xu-0ron/
华为笔试题
*/
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int,int> hash;
        for(int & a:answers){
            hash[a]++;
        }

        int res=0;

        for(auto& h:hash){
            int tmp=0;
            tmp = h.second / (h.first+1);
            if((h.second % (h.first+1))!=0){
                tmp +=1;
            }    
            res += tmp*(h.first+1);
        }
        return res;
    }
};

int main(){
    //[1, 1, 2]
    string t = "3    , 4";
    cout<<stoi(t)<<endl;
    // while(getline(cin,t)){
    //     //t不定长，怎么确定元素个数？
    //     t = t.substr(1,t.size()-2);
    //     // cout<<t<<endl;
    //     stringstream ss;
    //     ss<<t;
    //     string tmp;
    //     while(getline(ss,tmp,',')){
    //         cout<<stoi(tmp)<<" ";
    //     }
    //     cout<<endl;
    // }
    return 0;
}