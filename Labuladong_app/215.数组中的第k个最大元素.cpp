/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 *
 * https://leetcode-cn.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (64.70%)
 * Likes:    1631
 * Dislikes: 0
 * Total Accepted:    607.7K
 * Total Submissions: 939.5K
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 * 
 * 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: [3,2,1,5,6,4] 和 k = 2
 * 输出: 5
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
 * 输出: 4
 * 
 * 
 * 
 * 提示： 
 * 
 * 
 * 1 
 * -10^4 
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0, r = nums.size()-1;
        k = nums.size()-k;
        while(l<=r){
            int p = find_index(nums,l,r);
            if(p<k){
                //第k大在右边
                l = p+1;
            }
            else if(p>k){
                //第k大在左边
                r = p-1;
            }
            else if(p==k){
                return nums[p];
            }
        }
        return -1;
    }
    
int find_index(vector<int>&nums, int l, int r){
    //再[l,r]中找到交换的位置
    if(l==r) return l;
    int pivot = nums[l];
    int i=l,j=r+1;
    while(true){
        while(nums[++i]<pivot){
            if(i==r) break;
        }
        while(nums[--j]>pivot){
            if(j==l) break;
        }
        if(i>=j) break;
        swap(nums[i],nums[j]);
    }
    //[3,2,1,5,6,4]
    //     j i    
    //[1,2,3,5,6,4]
        
    swap(nums[l],nums[j]);
    return j;
}
void fast_sort(vector<int>&nums,int l,int r){
    if(l>=r) return;//
    int p = find_index(nums,l,r);
    fast_sort(nums,l,p-1);
    fast_sort(nums,p+1,r);
}
};


// @lc code=end

