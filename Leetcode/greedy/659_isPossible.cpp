#include <vector>
#include <iostream>
#include <algorithm>
#include<unordered_map>
#include<sstream>
using namespace std;
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,int> freq;
        unordered_map<int,vector<vector<int>>> need;
        for(auto &n:nums){
            freq[n]++;
        }
        for(auto &n:nums){
            if(freq[n]==0){
                continue;//很重要的一步，如果频率为0，表示该元素被用过了，
                //ferq起始都是>=1的。
            }


            //将n分配到某个子序列中
            if(need.count(n)&&need[n].size()>0){
                //优先接到之前的子序列
                // need[n]--;
                vector<int> seq = need[n].back();
                need[n].pop_back();
                freq[n]--;
                seq.push_back(n);
                need[n+1].push_back(seq);
                // need[n+1]++;//对n+1的需求加1，这样遍历到n+1的时候就知道有人要你
            }
            else if(freq[n]>0&&freq[n+1]>0&&freq[n+2]>0){
                //可以作为开头
                freq[n]--;
                freq[n+1]--;
                freq[n+2]--;
                need[n+3].push_back({n,n+1,n+2});
                // need[n+3]++;//对n+3的需求+1
            }
            //实在无法分配n
            else{
                return false;
            }
        }
        for(auto it:need){
            for(auto seq:it.second){
                for(auto v:seq){
                    cout<<v<<", ";
                }
                cout<<endl;
            }
        }
        return true;
    }
};



int main(){
    int a=1;
    stringstream ss;
    string s;
    while(getline(cin,s)){
        ss.clear();
        int t;
        ss<<s;
        vector<int> num;
        while (ss>>t)
        {
            num.push_back(t);
        }
        // num.push_back(stoi(s));
        // cout<<s<<endl;
        // for(auto n:num){
        // cout<<n<<' ';
        // }
        Solution asd;
        asd.isPossible(num);
    }

        
    return 0;
}