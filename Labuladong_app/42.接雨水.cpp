/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 *
 * https://leetcode-cn.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (60.55%)
 * Likes:    3362
 * Dislikes: 0
 * Total Accepted:    460.1K
 * Total Submissions: 759.6K
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出：6
 * 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
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
    int trap(vector<int>& height) {
        // return baoli(height);
        // return memo(height);
        return best(height);
    }
    int baoli(vector<int>& height){
        //暴力解法
        //每个i能撑多少水
        int res=0;//装水
        for(int i=0;i<height.size();i++){
            int l_height = height[i];
            for(int j=i;j>=0;j--){//注意等于0
                //往左找比自己大的
                l_height = max(l_height,height[j]);
            }
            int r_height = height[i];
            for(int j=i;j<height.size();j++){
                r_height = max(r_height,height[j]);
            }
            // cout<<min(l_height,r_height) - height[i]<<" ";
            res += min(l_height,r_height) - height[i];
        }
        return res;
    }
    int memo(vector<int>& height){
        //对每个位置i，它都有左边的最高，和右边的最高
        vector<int> l(height.size());
        vector<int> r(height.size());
        int l_max =0;
        for(int i=0;i<height.size();i++){
            //还可以压缩，
            l_max = max(height[i],l_max);
            l[i] =l_max;
        }
        int r_max=0;
        for(int i=height.size()-1;i>=0;i--){
            r_max = max(height[i],r_max);
            r[i] = r_max;
        }
        int res=0;
        for(int i=0;i<height.size();i++){
            res+= min(l[i],r[i]) - height[i];
        }
        return res;
    }
    int best(vector<int>& height){
        int l_max=0,r_max=0;
        int l=0,r=height.size()-1;
        int res=0;
        while(l<=r){
            l_max =max(l_max,height[l]);
            r_max = max(r_max,height[r]);
            if(l_max<r_max){
                res += l_max - height[l];
                l++;
            }
            else{
                res += r_max - height[r];
                r--;
            }
        }
        return res;
    }
};
// @lc code=end

