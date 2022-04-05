#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums;
        for(int i=1;i<=n;i++){
            nums.push_back(i);
        }
        backtrack(nums,0,k);
        return res;
    }
    void backtrack(vector<int>& nums, int start,int k){
        //start规定从数组的哪一位置开始，避免重复。

        //加个条件就是变成组合问题。
        if(k == track.size()){
            res.push_back(track);
            return;
        }
        
        //怎么遍历？
        for(int i=start; i<nums.size(); i++){
            //做选择，
            track.push_back(nums[i]);
            backtrack(nums,i+1,k);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
        }
    }
};