#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
/*candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 */
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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
        
        //怎么遍历？可以重复选择。
        for(int i=start; i<nums.size(); i++){
            //做选择，
            sum += nums[i];
            track.push_back(nums[i]);
            backtrack(nums,i,sum,target);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
            sum -= nums[i];
        }
    }
};