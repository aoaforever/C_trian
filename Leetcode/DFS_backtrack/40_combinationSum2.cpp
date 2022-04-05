#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

//数组有重复，只能使用一次
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());//让重复元素挨在一起。
        backtrack(candidates,0,0,target);
        return res;
    }
    void backtrack(vector<int>& nums, int start,int sum, int target){
        //start规定从数组的哪一位置开始，避免重复。

        //加个条件就是变成组合问题。
        if(sum == target){//思考，是每次递归都求一次和好？还是在递归中求前缀和好？
        //每次递归求和需要遍历一整个数组，因此第二种方法好。
            res.push_back(track);
            return;
        }
        if(sum > target){
            return;
        }
        
        //怎么遍历？不能重复选择。
        for(int i=start; i<nums.size(); i++){
            //做选择，
            if(i>start&&nums[i]==nums[i-1]){
                continue;
            }
            
            sum += nums[i];
            track.push_back(nums[i]);
            backtrack(nums,i+1,sum,target);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
            sum -= nums[i];
        }
    }

};