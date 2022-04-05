
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    
    map<pair<int,int>,bool> memo; 
    bool canPartition(vector<int>& nums) {
        
        int sum=0;
        for(auto& n:nums){
            sum += n;
        }
        if(sum%2==1){return false;}
        sum = sum/2;
        
        return dp(nums.size(),sum,nums);
    }

    //dp表示前i个物品下，能否装满w。
    bool dp(int i,int w,vector<int>&nums){
        pair<int,int> key(i,w);
        if(w==0){//如果背包装满了，那就成功了
            memo[key] = true;
            return memo[key];
        }
        if(i<1){
            return false;
        }
        
        if(memo.count(key)){
            return memo[key];
        }
        if(w-nums[i-1]<0){
            memo[key] = dp(i-1,w,nums);
            return memo[key];
        }
        else{
            memo[key] = dp(i-1,w,nums)||dp(i-1,w-nums[i-1],nums);
            return memo[key];
             
        }
    }
};

class Solution {
public:
    
    bool canPartition(vector<int>& nums) {
        
        int sum=0;
        for(auto& n:nums){
            sum += n;
        }
        if(sum%2==1){return false;}
        sum = sum/2;
        vector<vector<bool>> dp(nums.size()+1,vector<bool>(sum+1));

        //base case,在j=0下，不需要物品就可以装满。
        for(int i=0;i<=nums.size();i++){
            dp[i][0] = true;
        }
        //dp[i][j]的定义： 在前i个物品下，是否能够刚好装满j？
        for(int i=1;i<=nums.size();i++){
            for(int j=1;j<=sum;j++){
                if(j-nums[i-1]<0){
                    dp[i][j] = dp[i-1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                }        
            }
        }
        return dp[nums.size()][sum];
    }
};




// int main(){
//     pair<int,int> a(1,2);
//     // bool a = -1;
//     // cout<<pair<int,int>{1,2}
//     cout<<a.first<<a.second<<endl;
//     // printf("%d",a);
//     return 0;
// }