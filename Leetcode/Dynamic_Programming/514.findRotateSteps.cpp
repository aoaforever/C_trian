
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<char,vector<int>> h;
    vector<vector<int>> memo;
    int findRotateSteps(string ring, string key) {
        memo = vector<vector<int>>(ring.size(),vector<int>(key.size(),-1));
        for(int i=0;i<ring.size();i++){
            h[ring[i]].push_back(i);
        }
        return dp(ring,0,key,0);
    }
    //dp代表在ring[i]开始转动获得当前key[j]的最小步数
    int dp(string& ring, int i, string& key, int j){
        if(j>=key.size()) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int n = ring.size();
        int res = INT_MAX;
        if(h.count(key[j])){
            //对于当前key[j]，在ring中有多少处索引？
            vector<int> suoyins = h[key[j]];
            for(int suoyin:suoyins){//从ring中取出了对应字母的几个索引
                //波动指针的次数
                int delta = abs(i-suoyin);
                //确定是向左转还是向右转
                delta = min(delta,n-delta);
                //剩下的交给下一个子问题解决，将指针拨到ring[suoyin],继续输入key[j+1]...
                int subproblem = dp(ring,suoyin,key,j+1);
                res = min(res, 1+ delta+ subproblem);//按下按钮也算1次，转动delta次，子问题次。
            }
        }
        memo[i][j] = res;
        return memo[i][j];
    }
};