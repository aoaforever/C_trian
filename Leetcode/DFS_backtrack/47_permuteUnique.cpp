#include <iostream>
#include <vector>
#include <algorithm>
//包含重复数字。
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> track;
        vector<bool> used(nums.size(),false);
        sort(nums.begin(),nums.end());//重复数字挨在一起。
        dfs(nums,track,used);
        return res;
    }


    void dfs(vector<int>&nums,vector<int>&track,vector<bool> used){
        
        if(track.size()==nums.size()){
            res.push_back(track);
            return;
        }
        for(int i=0;i<nums.size();i++){//轮询一遍就是全排列。
            if(used[i]){//双重剪枝，如果当前被使用过了，就意味这不能在选了
                continue;
            }
            if(i>0&&nums[i]==nums[i-1]&&!used[i-1]){//这里是指不能有重复的排列。
                continue;
            }
            used[i] = true;
            track.push_back(nums[i]);//用一个数组存当前已经push的元素。
            dfs(nums,track,used);//然后继续下一个递归。如果已经存过某个元素，则进行下次循环（不是下次递归。）
            //erase(track,n);
            track.pop_back();//不需要erase
            used[i] = false;
        }

    }
};