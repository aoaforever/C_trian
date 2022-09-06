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

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        
        int dp_1=0,dp_2=0,dp;
        
        // 
        
        for(int i=0;i<nums.size();i++){
            dp = max(dp_1,dp_2+nums[i]);
            dp_2 = dp_1;
            dp_1 = dp;
        }
        return dp;
        
    }
};


/*大疆8月7日笔试题
给定一个数组，元素值代表价值，今天取出物品后，只能隔一天后，才能在取，求取得的物品的最大价值。
类似与股票冷冻期，但又不完全像。
*/

void dp_(vector<int>& nums){
    int n = nums.size();
    vector<vector<int>> dp(n+1,vector<int>(2));
    dp[0][0] = 0; // 第0天，没有拿，就是0
    dp[0][1] = INT_MIN;// 第0天，拿了，是不可能的，就是无限小
    dp[1][0] = 0;
    dp[1][1] = nums[0];

    for(int i=1; i<n;i++){
        dp[i+1][0] = max(dp[i][0],dp[i][1]);
        dp[i+1][1] = nums[i]+ max(dp[i][0],dp[i-1][1]);//如果今天取物品，那么只能根据昨天没取 或者前天取的状态进行转移。
    }

    int res = max(dp[n][0],dp[n][1]);
    cout<<res<<endl;
}

int main(int argc, char const *argv[])
{
    string s;
    getline(cin,s);
    stringstream ss;
    ss<<s;
    vector<int> nums;
    int tmp;
    while(ss>>tmp){
        nums.emplace_back(tmp);
    }
    dp_(nums);
    return 0;
}
