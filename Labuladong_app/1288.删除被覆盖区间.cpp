/*
 * @lc app=leetcode.cn id=1288 lang=cpp
 *
 * [1288] 删除被覆盖区间
 *
 * https://leetcode.cn/problems/remove-covered-intervals/description/
 *
 * algorithms
 * Medium (56.36%)
 * Likes:    73
 * Dislikes: 0
 * Total Accepted:    19.5K
 * Total Submissions: 34.5K
 * Testcase Example:  '[[1,4],[3,6],[2,8]]'
 *
 * 给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。
 * 
 * 只有当 c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。
 * 
 * 在完成所有删除操作后，请你返回列表中剩余区间的数目。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入：intervals = [[1,4],[3,6],[2,8]]
 * 输出：2
 * 解释：区间 [3,6] 被区间 [2,8] 覆盖，所以它被删除了。
 * 
 * 
 * 
 * 
 * 提示：​​​​​​
 * 
 * 
 * 1 <= intervals.length <= 1000
 * 0 <= intervals[i][0] < intervals[i][1] <= 10^5
 * 对于所有的 i != j：intervals[i] != intervals[j]
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
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]) return a[1]>b[1];
            return a[0]<b[0];
        });

        //存在合并就两种情况，太短合并， 合成一个长的
        int start = intervals[0][0], end = intervals[0][1];
        
        int res=0;
        for(int i=1;i<intervals.size();i++)
            {
            int cur_start = intervals[i][0];
            int cur_end = intervals[i][1];
            if(cur_end<=end){
                //你没了，直接被吞
                res++;
                continue;
            }
            else if(cur_start<=end&&cur_end>end){
                
                end = cur_end;
            }
            else if(cur_start>start){
                
                start = cur_start;
                end=cur_end;
            }
        }
        return intervals.size()-res;
    }
};
// @lc code=end

