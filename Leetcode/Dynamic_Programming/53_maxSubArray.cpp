#include <vector>
#include <limits.h>
using namespace std;

//不能用滑动串口
//dp数组的定义要好，以当前元素为结尾的最大和的连续子数组。

//还可以继续压缩空间。见pdf P443

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        for(int i=1;i<dp.size();i++){
            dp[i] = max(nums[i],dp[i-1]+nums[i]);
        }
        int res = INT_MIN;
        for(int i=0;i<dp.size();i++){
            res =max(res,dp[i]);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> memo;
    int maxSubArray(vector<int>& nums) {
        memo = vector<int>(nums.size(),-999);
        int res= INT_MIN;
        dp(nums,nums.size()-1,res);
        // int res=INT_MIN;
        // for(int i=0;i<memo.size();i++){
        //     res= max(res,memo[i]);
        // }
        return res;
    }

    //dp表示当前元素结尾的最大子序列和。
    int dp(vector<int>&nums, int n,int& res){
        if(n<0){
            return 0;
        }
        if(n==0){
            memo[n] = nums[0];
            return memo[n];
        }

        if (memo[n]!=-999) return memo[n];
        //子问题：
        int subproblem = dp(nums,n-1,res);//前一层的最大子数组和
        memo[n] = max(nums[n],subproblem+nums[n]);//那么这一层的最大子数组和为
        res= max(res,memo[n]);
        return memo[n];
    }
};