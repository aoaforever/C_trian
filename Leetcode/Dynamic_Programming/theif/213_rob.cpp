#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return max(nums[0],nums[1]);
        return max(rob_range(nums,0,nums.size()-2),rob_range(nums,1,nums.size()-1));
    }
    int rob_range(vector<int>& nums, int start, int end){
        //dp[N-1] 表示前N-1家能偷盗的最大金额。。
        int dp_0 = nums[start];
        int dp_1 = max(nums[start],nums[start+1]);

        for(int i=2+start;i<=end;i++){
            int tmp = dp_1;
            dp_1 = max(dp_0+nums[i],dp_1);
            dp_0 = tmp;
        }
        return dp_1;
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        return max(rob_range(nums,0,nums.size()-1),rob_range(nums,1,nums.size()));
    }

    int rob_range(vector<int>& nums,int start,int end) {
        if(nums.size()==1) return nums[0];
        
        int dp_1=0,dp_2=0,dp;
        
        // 
        
        for(int i=start;i<end;i++){
            dp = max(dp_1,dp_2+nums[i]);
            dp_2 = dp_1;
            dp_1 = dp;
        }
        return dp;
        
    }
};
