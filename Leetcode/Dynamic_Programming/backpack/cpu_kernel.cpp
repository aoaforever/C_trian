#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*

题目的大概意思：一种双核CPU的两个核能够同时的处理任务，现在有n个已知数据量的任务需要交给CPU处理，假设已知CPU的每个核1秒可以处理1kb，每个核同时只能处理一项任务。n个任务可以按照任意顺序放入CPU进行处理，现在需要设计一个方案让CPU处理完这批任务所需的时间最少，求这个最小的时间。 

输入包括两行：
第一行为整数n(1 ≤ n ≤ 50)
第二行为n个整数length[i](1024 ≤ length[i] ≤ 4194304)，表示每个任务的长度为length[i]kb，每个数均为1024的倍数。
输出一个整数，表示最少需要处理的时间。
*/

void solution(vector<int>& nums, int sum){
    //dp表示背包的装入的价值
    int target = sum/2;
    vector<vector<int>> dp(nums.size()+1,vector<int>(target+1,0));
    for(int i=0;i<=target;i++){
        dp[0][i] =0;
    }

    for(int i=1;i<=nums.size();i++){
        for(int j=1;j<=target;j++){
            if(j<nums[i-1]) continue;//如果背包容量小于物品容量，则跳过
            dp[i][j] = max(dp[i-1][j],dp[i-1][j-nums[i-1]]+nums[i-1]);
        }
    }
    //如果是target-dp[nums.size()][target]的话，那就是表示两个子集的最小和差。
    cout<<(sum-dp[nums.size()][target])*1024<<endl;
}

int main(){

    int n;
    cin>>n;
    vector<int> nums(n);
    int sum =0;
    for(int i=0;i<n;i++){
        cin>>nums[i];
        nums[i] = nums[i]/1024;
        sum += nums[i];
    }
    solution(nums,sum);

    return 0;
}