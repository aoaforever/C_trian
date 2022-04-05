#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        //dp[N-1] 表示前N-1家能偷盗的最大金额。。
        if (nums.size()==1){
            return nums[0];
        }
        int dp[nums.size()];

        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);

        for(int i=2;i<nums.size();i++){
            dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
        }
        return dp[nums.size()-1];
    }
};

//用两个状态表示
class Solution {
public:
    int rob(vector<int>& nums) {
        //dp[i][0,1] : 表示第i家0：不偷，1偷的 金额。
        int n=nums.size();
        int dp[n+1][2];
        dp[0][0] = 0;
        dp[0][1] = INT_MIN;

        for(int i =1;i<=n;i++){
            dp[i][0] =max(dp[i-1][0],dp[i-1][1]);//今天不偷，前一天可能也不偷，也可能偷。
            dp[i][1] = dp[i-1][0];//如果今天偷，昨天必须没偷。
        }
        return max(dp[n][0],dp[n][1]);
    }
};
