/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] 合并区间
 *
 * https://leetcode.cn/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (48.58%)
 * Likes:    1500
 * Dislikes: 0
 * Total Accepted:    452.6K
 * Total Submissions: 930.8K
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]
 * 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：intervals = [[1,4],[4,5]]
 * 输出：[[1,5]]
 * 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= intervals.length <= 10^4
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 10^4
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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]) return a[1]>b[1];
            return a[0]<b[0];
        });

        //存在合并就两种情况，太短合并， 合成一个长的
        int start = intervals[0][0], end = intervals[0][1];
        vector<vector<int>> res = {{start,end}};
        for(vector<int>& i :intervals){
            int cur_start = i[0];
            int cur_end = i[1];
            if(cur_end<=end){
                //你没了，直接被吞
                continue;
            }
            else if(cur_start<=end&&cur_end>end){
                res.back()[1]=cur_end;
                end = cur_end;
            }
            else if(cur_start>start){
                res.push_back({cur_start,cur_end});
                start = cur_start;
                end=cur_end;
            }
        }
        return res;
    }
};
// @lc code=end

