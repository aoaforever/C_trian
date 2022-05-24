
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

class Solution {
public:
    unordered_map<char,vector<int>> charToindex;
    unordered_map<string,int> memo;
    int findRotateSteps(string ring, string key) {
        for(int i=0;i<ring.size();i++){
            charToindex[ring[i]].push_back(i);
        }
        return dp(ring,0,key,0);
    }
    int dp(string& ring, int i, string & key , int j){
        //我现在在i，和j，转动到key[j]的最少次数
        //但是，i到key[j]可能有多条路径
        //那么就每条路径都算出来，取最小值

        //为了避免每次递归都去调用函数找位置，直接用一个哈希表记录所有字母的位置
        if(j==key.size()) return 0;//是0不是1 ，已经找完了，不需要再转了
        
        string a = to_string(i)+" "+to_string(j);
        if(memo.count(a)) return memo[a];
        int n = ring.size();
        char target = key[j];
        int res=INT_MAX;
        for(auto k : charToindex[target]){
            //穷举所有的位置，取最小值
            // int left = k+ring.size()-i;//往左转的步数
            // int right = i-k; //往右转的步数
            // int step = min(left,right);
            int delta = abs(i-k);//是一个环，所以只能用这种情况
            int step = min(delta,n-delta);

            int subproblem = dp(ring,k,key,j+1);
            res = min(res, subproblem+step+1);
        }
        memo[a] = res;
        return res;
    }
};