#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        backtrack(nums,0);
        return res;
    }
        void backtrack(vector<int>& nums, int start){
        //start规定从数组的哪一位置开始，避免重复。

        //每次递归都是一个子集，并且不会重复
        res.push_back(track);
        //怎么遍历？
        for(int i=start; i<nums.size(); i++){
            if(i>start&&nums[i]==nums[i-1]){//这个成立的条件是，数组有序。
                continue;
            }
            //做选择，
            track.push_back(nums[i]);
            backtrack(nums,i+1);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
        }
    }
};