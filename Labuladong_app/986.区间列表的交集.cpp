/*
 * @lc app=leetcode.cn id=986 lang=cpp
 *
 * [986] 区间列表的交集
 *
 * https://leetcode.cn/problems/interval-list-intersections/description/
 *
 * algorithms
 * Medium (68.38%)
 * Likes:    286
 * Dislikes: 0
 * Total Accepted:    44.9K
 * Total Submissions: 65.6K
 * Testcase Example:  '[[0,2],[5,10],[13,23],[24,25]]\n[[1,5],[8,12],[15,24],[25,26]]'
 *
 * 给定两个由一些 闭区间 组成的列表，firstList 和 secondList ，其中 firstList[i] = [starti, endi] 而
 * secondList[j] = [startj, endj] 。每个区间列表都是成对 不相交 的，并且 已经排序 。
 * 
 * 返回这 两个区间列表的交集 。
 * 
 * 形式上，闭区间 [a, b]（其中 a ）表示实数 x 的集合，而 a  。
 * 
 * 两个闭区间的 交集 是一组实数，要么为空集，要么为闭区间。例如，[1, 3] 和 [2, 4] 的交集为 [2, 3] 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：firstList = [[0,2],[5,10],[13,23],[24,25]], secondList =
 * [[1,5],[8,12],[15,24],[25,26]]
 * 输出：[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：firstList = [[1,3],[5,9]], secondList = []
 * 输出：[]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：firstList = [], secondList = [[4,8],[10,12]]
 * 输出：[]
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：firstList = [[1,7]], secondList = [[3,10]]
 * 输出：[[3,7]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 
 * firstList.length + secondList.length >= 1
 * 0 i < endi 
 * endi < starti+1
 * 0 j < endj 
 * endj < startj+1
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
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        //已经排好序
        int i=0,j=0;
        vector<vector<int>> res;
        while (i<firstList.size()&&j<secondList.size())
        {
            cout<<i<<" "<<j<<endl;
            vector<int>& f= firstList[i];
            vector<int>& s= secondList[j];

            //要先判断不相交的情况
            if(s[0]<=f[1]&&s[1]>=f[0]){
                //相交
                int start = max(f[0],s[0]);
                int end = min(f[1],s[1]);
                res.push_back({start,end});
            }
            

            if(f[1]<s[1]){
                i++;
            }
            else j++;
        }
        return res;
    }
};
// @lc code=end

