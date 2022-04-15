#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();i++){
            int target = 0 - nums[i];
            vector<vector<int>> r = twoSum(nums,i+1,target);
            //添加当前元素到所有数组中
            for(vector<int>& v:r){
                v.push_back(nums[i]);
                res.push_back(v);
            }
            while(i+1<nums.size()&&nums[i]==nums[i+1]) i++;//必须跳过
        }
        return res;
    }

    vector<vector<int>> twoSum(vector<int>&nums,int l,int target){
        //返回多组数组
        //默认已经排好序
        int r = nums.size()-1;
        vector<vector<int>> res;
        while(l<r){
            int left = nums[l], right = nums[r];
            int sum = nums[l]+nums[r];
            if(sum<target){
                while(l<r&&left==nums[l]) l++;
            }
            else if(sum>target){
                while(l<r&&right==nums[r]) r--;
            }
            else if(sum==target){
                res.push_back({nums[l],nums[r]});
                //避免重复添加
                while(l<r&&left==nums[l]) l++;
                while(l<r&&right==nums[r]) r--;
            }
        }
        return res;
    }
};