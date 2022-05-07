#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//超时做法
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]){
                return a[1]>b[1];
            }
            return a[0]<b[0];
        });
        //怎么对h做最长递增子序列
        //dp[i]以i结尾的最长递增子序列。
        vector<int> dp(envelopes.size(),1);
        for(int i=1;i<envelopes.size();i++){
            //只管当前和之前所有
            for(int j=0;j<i;j++){
                if(envelopes[i][1]>envelopes[j][1]){
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
        }
        int res = -2;
        for(int i=0;i<envelopes.size();i++){
            res = max(res,dp[i]);
        }
        return res;
    }
};

//扑克牌
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]){
                return a[1]>b[1];
            }
            return a[0]<b[0];
        });
        int piles =0;//牌堆
        vector<int> top(envelopes.size());
        for(int i=0;i<envelopes.size();i++){
            int target = envelopes[i][1];
            int l=0, r =piles;//左闭右开
            while(l<r){
                int mid = l+(r-l)/2;
                if(top[mid]<target){
                    l = mid+1;
                }
                else if(top[mid]>target){
                    r = mid;
                }
                else {
                    r= mid;
                }
            }
            if(l==piles) piles++;
            top[l] = target;
        }
        return piles;
    }
};