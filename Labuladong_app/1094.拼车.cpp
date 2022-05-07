/*
 * @lc app=leetcode.cn id=1094 lang=cpp
 *
 * [1094] 拼车
 *
 * https://leetcode-cn.com/problems/car-pooling/description/
 *
 * algorithms
 * Medium (55.79%)
 * Likes:    163
 * Dislikes: 0
 * Total Accepted:    43.5K
 * Total Submissions: 78.1K
 * Testcase Example:  '[[2,1,5],[3,3,7]]\n4'
 *
 * 车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）
 * 
 * 给定整数 capacity 和一个数组 trips ,  trip[i] = [numPassengersi, fromi, toi] 表示第 i
 * 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。
 * 
 * 当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：trips = [[2,1,5],[3,3,7]], capacity = 4
 * 输出：false
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：trips = [[2,1,5],[3,3,7]], capacity = 5
 * 输出：true
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= trips.length <= 1000
 * trips[i].length == 3
 * 1 <= numPassengersi <= 100
 * 0 <= fromi < toi <= 1000
 * 1 <= capacity <= 10^5
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<int> nums(1000,0);
        Difference d(nums);
        for(vector<int>& t:trips){
            int val = t[0];
            int l = t[1];
            int r = t[2]-1;//由于这一站下车，因此这一战不会增加人数
            d.increment(l,r,val);
        }
        nums = d.result();
        for(auto& n:nums){
            if(n>capacity){return false;}
        }
        return true;
    }
    
    class Difference{
    public:
        Difference(vector<int>&nums){
            diff.resize(nums.size(),0);
            // diff[0] = nums[0];
            // for(int i=1;i<diff.size();i++){
            //     diff[i] = nums[i] - nums[i-1];
            // }
        }
        void increment(int l,int r,int val){
            //给闭区间[l,r]增加val,下标l,r
            diff[l] += val;
            if(r+1<diff.size()){
                diff[r+1] -= val;
            }
        }
        vector<int>& result(){
            vector<int> num(diff.size());
            num[0] = diff[0];
            for(int i=1;i<num.size();i++){
                num[i] = num[i-1] + diff[i];
            }
            return num;
        }
    private:    
        vector<int> diff;
    };  
};
// @lc code=end

int main(){
    vector<vector<int>> trips={{2,1,5},{3,3,7}};
    Solution s;
    s.carPooling(trips,4);
    
    return 0;
}