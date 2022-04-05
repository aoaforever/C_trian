
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// 全排列对于子集的问题在于，全排列前面的元素能够被重新组合。

//这个算法的缺点是不能有重复的数字。
//然而，有重复数字说明会有重复的一匹路。
// class Solution {
// public:
//     vector<vector<int>> res;
//     vector<vector<int>> permute(vector<int>& nums) {
//         vector<int> track;
//         dfs(nums,track);
//         return res;
//     }
//     bool find(vector<int>& n,int target){
//         for(const auto& a:n){
//             if(a==target){
//                 return true;
//             }
//         }
//         return false;
//     }
//     void erase(vector<int>&track,int target){
//         auto it = track.begin();
//         cout<<"target:"<<target<<endl;
//         for(;it!=track.end();it++){
//             cout<<*it<<endl;
//             if(*it==target){
//                 track.erase(it);
//             }
//         }
//     }
//     void dfs(vector<int>&nums,vector<int>&track){
//         if(track.size()==nums.size()){
//             res.push_back(track);
//             return;
//         }
//         for(const auto& n:nums){//轮询一遍就是全排列。
//             if(find(track,n)){
//                 continue;
//             }
//             track.push_back(n);//用一个数组存当前已经push的元素。
//             dfs(nums,track);//然后继续下一个递归。如果已经存过某个元素，则进行下次循环（不是下次递归。）
//             //erase(track,n);
//             track.pop_back();//不需要erase
//         }

//     }
// };

//用used数组做剪枝
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> track;
        vector<bool> used(nums.size(),false);
        dfs(nums,track,used);
        return res;
    }


    void dfs(vector<int>&nums,vector<int>&track,vector<bool> used){
        if(track.size()==nums.size()){
            res.push_back(track);
            return;
        }
        for(int i=0;i<nums.size();i++){//轮询一遍就是全排列。
            if(used[i]){
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
//用交换进行的回溯算法
class Solution {

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(res,nums,0,nums.size());
        return res;
    }
    void backtrack(vector<vector<int>>&res, vector<int>&output,int first, int len){
        //停止条件
        if(first==len){
            res.push_back(output);
            return;
        }
        //路径选择
        for(int i = first; i<len; i++){
            //路径选择，选i作为头部
            swap(output[i],output[first]);
            //然后进行下一次递归
            backtrack(res,output,first+1,len);
            //递归完，撤销选择
            swap(output[i],output[first]);
        }

    }
};

int main(){

    vector<int> a{-1,2,-1,3,};
    Solution s;
    vector<vector<int>> res = s.permute(a);
    for(auto & v : res){
        for(auto& p:v){
            cout<<p<<" ";
        }
        cout<<endl;
    }

}