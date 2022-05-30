/*
 * @lc app=leetcode.cn id=391 lang=cpp
 *
 * [391] 完美矩形
 *
 * https://leetcode.cn/problems/perfect-rectangle/description/
 *
 * algorithms
 * Hard (46.31%)
 * Likes:    220
 * Dislikes: 0
 * Total Accepted:    23.2K
 * Total Submissions: 50.1K
 * Testcase Example:  '[[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]'
 *
 * 给你一个数组 rectangles ，其中 rectangles[i] = [xi, yi, ai, bi]
 * 表示一个坐标轴平行的矩形。这个矩形的左下顶点是 (xi, yi) ，右上顶点是 (ai, bi) 。
 * 
 * 如果所有矩形一起精确覆盖了某个矩形区域，则返回 true ；否则，返回 false 。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 * 输出：true
 * 解释：5 个矩形一起可以精确地覆盖一个矩形区域。 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 * 输出：false
 * 解释：两个矩形之间有间隔，无法覆盖成一个矩形。
 * 
 * 示例 3：
 * 
 * 
 * 输入：rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 * 输出：false
 * 解释：因为中间有相交区域，虽然形成了矩形，但不是精确覆盖。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= rectangles.length <= 2 * 10^4
 * rectangles[i].length == 4
 * -10^5 <= xi, yi, ai, bi <= 10^5
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        long area=0;
        set<vector<int>> count;
        int L0 = INT_MAX;
        int L1 = INT_MAX;
        int R0 = INT_MIN;
        int R1 = INT_MIN;
        for(auto& r:rectangles){
            area += long((r[2]-r[0]))*(r[3]-r[1]);

            L0 = min(L0,r[0]);
            L1 = min(L1,r[1]);
            R0 = max(R0,r[2]);
            R1 = max(R1,r[3]);


            vector<int> lu = {r[0],r[3]};
            vector<int> ll = {r[0],r[1]};
            vector<int> ru = {r[2],r[3]};
            vector<int> rl = {r[2],r[1]};
            if(count.count(lu)) count.erase(lu);
            else count.insert(lu);
            if(count.count(ll)) count.erase(ll);
            else count.insert(ll);
            if(count.count(ru)) count.erase(ru);
            else count.insert(ru);
            if(count.count(rl)) count.erase(rl);
            else count.insert(rl);
        }

        
        long new_area = long((R0-L0))*(R1-L1);
        cout<<new_area<<" "<< area<<endl;
        cout<<count.size();
        if(area!=new_area) return false;
        if(count.size()!= 4) return false;
        vector<int> lu = {L0,R1};
        vector<int> ll = {L0,L1};
        vector<int> ru = {R0,R1};
        vector<int> rl = {R0,L1};
        if(!count.count(lu)) return false;
        if(!count.count(ll)) return false;
        if(!count.count(ru)) return false;
        if(!count.count(rl)) return false;

        return true;
    }
};
// @lc code=end

