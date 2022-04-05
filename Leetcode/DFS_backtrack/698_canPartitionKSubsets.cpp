#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if(k>nums.size()) return false;
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum % k !=0) return false;
        int target = sum/k;
        //即使上面排除了一些不行的情况，然而还有些情况需要递归才能知道是错误的。

        sort(nums.begin(),nums.end(),std::greater<int>());//不加排序，会很快超时，加了排序，迟一点超时。因此需要第二种解法。
        vector<int> bucket(k,0);
        return backtrack(nums,0,bucket,target);
    }
    //以数组视角递归数组
    bool backtrack(vector<int>& nums, int k,vector<int>&bucket, int target){
        //停止条件
        if(k==nums.size()){
            //元素选完了。判断桶的和是不是达标
            for(auto& b:bucket){
                if(b!=target){
                    return false;
                }
            }
            return true;
        }
        //对于当前元素，有k个桶可以放置
        for(int i=0;i<bucket.size();i++){
            //剪枝
            if(bucket[i] + nums[k] > target){
                continue;//放下一个桶吧。
            }
            //将元素放进桶
            bucket[i] += nums[k];
            
            if(backtrack(nums,k+1,bucket,target)){
                return true;}
                //那么就肯定在这里放递归了。
            //撤销放进桶
            bucket[i] -= nums[k];
        }

        //如果所有桶都没返回true
        return false;
    }


};

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if(k>nums.size()) return false;
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum % k !=0) return false;
        int target = sum/k;
        //即使上面排除了一些不行的情况，然而还有些情况需要递归才能知道是错误的。

        sort(nums.begin(),nums.end(),std::greater<int>());//不加排序，会很快超时，加了排序，迟一点超时。因此需要第二种解法。
        // vector<int> bucket(k,0);
        vector<bool> used(nums.size(),false);
        return backtrack(k,0,nums,0,used,target);
    }
    //以桶视角递归数组
    //k个桶，该桶的sum，数组， 数组下标，使用过，目标
    bool backtrack(int k, int bucket, vector<int>&nums, int start, vector<bool>&used, int target){
        if(k==0){
            //确实用递增不好确定结束条件，因此递减是最好的
            //桶都分配完了，那肯定是成功了
            return true;
        }
        //判断当前桶是否
        if(bucket==target){
            //装满了当前桶，递归穷举下一个桶的选择
            return backtrack(k-1,0,nums,0,used,target);
        }

        //bucket代表第k个桶的sum
        //现在是第k个桶去寻找nums，填满桶
        //从start开始向后探查有效的nums[i]装入当前桶，这里你没想到
        for(int i=start;i<nums.size();i++){
            if(used[i]){
                continue;//如果当前元素用过了，那就下个元素
            }
            if(bucket+nums[i]>target) continue;//如果当前元素太大，那就下个元素
            //选择该元素放进桶里
            bucket += nums[i];
            used[i] = true;

            //递归
            if(backtrack(k,bucket,nums,i+1,used,target)){
                return true;
            };

            //撤销选择
            bucket -= nums[i];
            used[i] = false;
        }

        //穷举了所有数字，都无法装满当前桶。
        return false;
    }

    
};