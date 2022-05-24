#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<int,vector<vector<int>>> rudu;
    int src;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //找入度
        this->src = src;
        for(vector<int>& f: flights){
            int from = f[0];
            int to = f[1];
            int price = f[2];
            rudu[to].push_back(vector<int>({from,price}));
            // rudu[to].push_back(vector<int>({from,price}));
            // rudu[to].push_back();//我知道是谁来我这，并且来我这的价格
        }
        return  dp(dst,k);
    }
    // 只需要一个目的地和k个中转站，就能知道最便宜的路线。
    int dp(int dst,int k){
        if(dst == src) return 0;//从某个点到达src的费用肯定是0.
        if(k==-1) return -1;//经过-1个中转站的费用肯定是error。
        //为什么需要将k个节点转换成k+1个边？
        //经过一个节点到达dst，表示有2条边。
        //边=路径的每个价格。
        int res = INT_MAX;
        for(auto& r : rudu[dst]){//到达该目的地的所有路径，取最小值
            int from = r[0];
            int price = r[1];
            int subproblem = dp(from,k-1);
            if(subproblem!=-1){//跳过无解的情况，
                res = min(res, subproblem+price);
            }
            
        }

        return res;
    }
};

class Solution {
public:
    unordered_map<int,vector<vector<int>>> indegree;
    vector<vector<int>> memo;
    int src,dst;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        k = k+1;//k个中转就是k+1条边
        this->src = src;
        this->dst = dst;
        memo = vector<vector<int>>(n,vector<int>(k+1,-666));
        for(vector<int>&f:flights){
            int from = f[0];
            int to =f[1];
            int price = f[2];

            indegree[to].push_back({from,price});
        }
        return dp(dst,k);
    }
    int dp(int i,int k){//定义了到达i的k条边最低价格，那么在哪里更新？
        
        if(i==src){//到达目的地了
            return 0;
        }
        //if的顺序不能乱，如果你中转次数为0了，但是你到了目的地了，那就是成功啊
        if(k==0) return -1;//不允许中转了
        if(memo[i][k]!=-666) return memo[i][k];
        //到达i有许多路径，穷举，求最小值
        auto& from = indegree[i];
        int res = INT_MAX;
        for(vector<int>& f:from){
            int comfrom = f[0];
            int price = f[1];
            int subproblem = dp(comfrom,k-1);
            if(subproblem==-1) continue;//跳过无解情况，不存在这样的路线
            res =min(subproblem+price,res);

        }
        res = res==INT_MAX?-1:res;
        memo[i][k] = res;
        return res;

    }
};