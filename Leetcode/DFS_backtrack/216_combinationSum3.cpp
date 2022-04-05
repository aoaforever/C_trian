#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

//数组无重复，只能使用一次。
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> nums;
        for(int i=1;i<=9;i++){
            nums.push_back(i);
        }
        backtrack(nums,0,0,k,n);
        return res;
    }
    void backtrack(vector<int>& nums, int start,int sum, int size,int target){
        //start规定从数组的哪一位置开始，避免重复。

        //加个条件就是变成组合问题。
        if(sum == target&& size == track.size()){//思考，是每次递归都求一次和好？还是在递归中求前缀和好？
        //每次递归求和需要遍历一整个数组，因此第二种方法好。
            res.push_back(track);
            return;
        }
        if(sum > target || track.size() > size){
            return;
        }
        
        //怎么遍历？不能重复选择。
        for(int i=start; i<nums.size(); i++){
            //做选择，
            sum += nums[i];
            track.push_back(nums[i]);
            backtrack(nums,i+1,sum,size,target);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
            sum -= nums[i];
        }
    }

};