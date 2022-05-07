/*
 * @lc app=leetcode.cn id=1109 lang=cpp
 *
 * [1109] 航班预订统计
 *
 * https://leetcode-cn.com/problems/corporate-flight-bookings/description/
 *
 * algorithms
 * Medium (60.47%)
 * Likes:    340
 * Dislikes: 0
 * Total Accepted:    77.5K
 * Total Submissions: 128K
 * Testcase Example:  '[[1,2,10],[2,3,20],[2,5,25]]\n5'
 *
 * 这里有 n 个航班，它们分别从 1 到 n 进行编号。
 * 
 * 有一份航班预订表 bookings ，表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] 意味着在从
 * firsti 到 lasti （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
 * 
 * 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
 * 输出：[10,55,45,25,25]
 * 解释：
 * 航班编号        1   2   3   4   5
 * 预订记录 1 ：   10  10
 * 预订记录 2 ：       20  20
 * 预订记录 3 ：       25  25  25  25
 * 总座位数：      10  55  45  25  25
 * 因此，answer = [10,55,45,25,25]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：bookings = [[1,2,10],[2,2,15]], n = 2
 * 输出：[10,25]
 * 解释：
 * 航班编号        1   2
 * 预订记录 1 ：   10  10
 * 预订记录 2 ：       15
 * 总座位数：      10  25
 * 因此，answer = [10,25]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 2 * 10^4
 * 1 <= bookings.length <= 2 * 10^4
 * bookings[i].length == 3
 * 1 <= firsti <= lasti <= n
 * 1 <= seatsi <= 10^4
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
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> nums(n,0);
        Difference d(nums);
        for(vector<int>& b:bookings){
            int l = b[0]-1;//编号从1开始的，所以要减1
            int r = b[1]-1;
            int val = b[2];
            d.increment(l,r,val);
        }
        return d.result();
    }
    class Difference{
public:
    Difference(vector<int>&nums){
        diff.resize(nums.size());
        diff[0] = nums[0];
        for(int i=1;i<diff.size();i++){
            diff[i] = nums[i] - nums[i-1];
        }
    }
    void increment(int l,int r,int val){
        //给闭区间[l,r]增加val,下标l,r
        diff[l] += val;
        if(r+1<diff.size()){
            diff[r+1] -= val;
        }
    }
    vector<int> result(){//要返回复制，而不是引用，因为这个函数调用完，临时变量就被销毁了，引用个屁
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

