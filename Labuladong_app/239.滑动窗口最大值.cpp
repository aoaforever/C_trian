/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 *
 * https://leetcode-cn.com/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (49.83%)
 * Likes:    1566
 * Dislikes: 0
 * Total Accepted:    277.6K
 * Total Submissions: 557.2K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
 * 个数字。滑动窗口每次只向右移动一位。
 * 
 * 返回 滑动窗口中的最大值 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
 * 输出：[3,3,5,5,6,7]
 * 解释：
 * 滑动窗口的位置                最大值
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 * ⁠1 [3  -1  -3] 5  3  6  7       3
 * ⁠1  3 [-1  -3  5] 3  6  7       5
 * ⁠1  3  -1 [-3  5  3] 6  7       5
 * ⁠1  3  -1  -3 [5  3  6] 7       6
 * ⁠1  3  -1  -3  5 [3  6  7]      7
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1], k = 1
 * 输出：[1]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        monotonicqueue q;
        vector<int> res;
        for(int i=0;i<nums.size();i++){
            if(i<k-1){//这里也要注意
                q.push(nums[i]);
            }//当达到k长度的时候才进行添加结果
            else{
                q.push(nums[i]);
                res.push_back(q.getfirst());
                q.pop(nums[i-k+1]);//这里要注意
                
            }
        }
        return res;
    }
    class monotonicqueue{
        public:
            void push(int n){
                while (!q.empty()&&q.back()<n)
                {
                    q.pop_back();
                }
                q.push_back(n);
                
            }
            int getfirst(){
                return q.front();
            }
            void pop(int target ){
                //为什么需要判断才删除
                //因为有可能当前要删除的元素在push的时候就已经被删除了
                if(!q.empty()&&target==q.front()){
                    q.pop_front();
                }
            }
        private:
            deque<int> q;
    };
};
// @lc code=end

