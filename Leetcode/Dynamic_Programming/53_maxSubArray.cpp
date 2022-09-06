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

class Solution {
public:
    vector<int> memo;
    int maxSubArray(vector<int>& nums) {
        memo.resize(nums.size(),-1);
        dp(nums,nums.size()-1);
        int res=INT_MIN;
        for(auto i:memo){
            res = max(res,i);
        }
        return res;
    }
    int dp(vector<int>& nums,int index){
        //dp[index]以index为结尾的最大和的连续子数组
        if(index<0){
            return 0;
        }
        if(memo[index]!=-1) return memo[index];
        int sp = dp(nums,index-1);
        int res=0;
        res = max(nums[index],sp+nums[index]);
        // cout<<res<<endl;
        // memo[index] =max(res,0); //[-1]
        memo[index] =res;
        return memo[index];
    }

};

/*
延伸——获取最大序列的起始和结束位置
可以使用我们的第一种方法也就是动态规划的方法来找到这个位置，将以这个元素结尾的的最大子序列的位置找出来，然后每次比较最大值的时候更新一下最大值的位置就行了
*/

public int maxSubArrayPosition(int[] nums) {
    if (nums == null) {
        return 0;
    }

    int start = 0;
    int end = 0;
    int subStart = 0;
    int subEnd = 0;
    int max = nums[0];    // 全局最大值
    int subMax = nums[0];  // 前一个子组合的最大值
    for (int i = 1; i < nums.length; i++) {
        if (subMax > 0) {
            // 前一个子组合最大值大于0，正增益，更新最后元素位置
            subMax = subMax + nums[i];
            subEnd++;
        } else {
            // 前一个子组合最大值小于0，抛弃前面的结果，更新当前最大值位置
            subMax = nums[i];
            subStart = i;
            subEnd = i;
        }
        // 计算全局最大值，更新位置，将全局最优解的位置更新
        if (subMax > max) {
            max = subMax;
            start = subStart;
            end = subEnd;
        }
    }

    System.out.println("[" + start + ","+ end +"]");
    return max;

作者：lizhiqiang-3
链接：https://leetcode.cn/problems/maximum-subarray/solution/zheng-li-yi-xia-kan-de-dong-de-da-an-by-lizhiqiang/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。