/*
        1
      2   3
    1  9 4  5    

//[1 2 3 1 9 4 5]
*/

#include <bits/stdc++.h>

using namespace std;


void help(vector<int>& nums){
    int n = nums.size();
    int k = n/2;//k以后的节点都是叶子节点，不包括k
    vector<int> dp(n+1);
    for(int i = n;i>k;i--){
        dp[i] = nums[i-1];
    }

    for(int i=k;i>=1;i--){
        // if(i*2>n){
        //     //没有子节点，不可能情况
        // }
        if(i*2+1>n){
            //没有右节点，只能选择左节点
            dp[i] = dp[i*2] + nums[i-1];
            continue;
        }
        dp[i] = max(dp[i*2],dp[i*2+1]) + nums[i-1];
    }
    cout<<dp[1]<<endl;

}

int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }    

    help(nums);
    return 0;
}
