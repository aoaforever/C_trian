
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




class Solution {
public:
    vector<bool> used;
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%2!=0) return false;
        int target = sum/2;
        sort(nums.begin(),nums.end(),greater<int>());
        used.resize(nums.size(),false);
        return dp(nums,0,target);
    }
    //这种可以跳跃数字的怎么搞？

    //那就是选择所有的nums，组成target一次就可以了
    bool dp(vector<int>&nums,int index,int target){
        if(target==0) return true;

        for(int i = index;i<nums.size();i++){
            if(used[i]) continue;
            if(target-nums[i]<0) continue;//不装入背包                
            else {
                used[i] = true;
                if(dp(nums,i+1,target-nums[i])){
                    return true;
                }//装入背包
                used[i] =false;
            }
        }
        //如果遍历了所有元素都组成不了，那就是错误
        
        return false;
    }
};


//以数字视角，由于只有一个桶，也就是0-1背包，完全优化之后就是下面的下面的解法
class Solution {
public:
    
    unordered_map<string,bool> memo;
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%2!=0) return false;
        int target = sum/2;
        // sort(nums.begin(),nums.end(),greater<int>());

        return dp(nums,0,target);
    }
    //这种可以跳跃数字的怎么搞？

    //那就是选择所有的nums，组成target一次就可以了
    bool dp(vector<int>&nums,int index,int target){
        if(target==0) return true;
        if(target<0||index>=nums.size()) return false;

        string key = to_string(index)+","+to_string(target);
        if(memo.count(key)) return memo[key];
        
        // if(target-nums[index]<0)  res = dp(nums,index+1,target);
        bool res= dp(nums,index+1,target-nums[index])||dp(nums,index+1,target);//顺序不能反
        
        //如果遍历了所有桶都组成不了，那就是错误
        memo[key] =res;
        return res;
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