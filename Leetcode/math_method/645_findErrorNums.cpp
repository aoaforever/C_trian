/*
 * @lc app=leetcode.cn id=645 lang=cpp
 *
 * [645] 错误的集合
 *
 * https://leetcode-cn.com/problems/set-mismatch/description/
 *
 * algorithms
 * Easy (41.86%)
 * Likes:    267
 * Dislikes: 0
 * Total Accepted:    82.7K
 * Total Submissions: 197.8K
 * Testcase Example:  '[1,2,2,4]'
 *
 * 集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，导致集合 丢失了一个数字 并且
 * 有一个数字重复 。
 * 
 * 给定一个数组 nums 代表了集合 S 发生错误后的结果。
 * 
 * 请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,2,2,4]
 * 输出：[2,3]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,1]
 * 输出：[1,2]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 
 * 1 
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <stdio.h>
using namespace std;
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int all=0;
        for(int i=1;i<=nums.size();i++){
            all ^= i; 
        }
        for(int&n :nums){
            all ^= n;
        }
        // cout<<all<<endl;
        //这样all就包括了重复和丢失的数字，要把他提取出来
        int rightone = all &(-all);
        // cout<<rightone<<endl;
        int x=0,y=0;
        for(int i=1;i<=nums.size();i++){
            if((rightone& i) ==0 ){
                x ^= i;
            }
            else y ^= i;
        }
        for(int&n:nums){
            if((n&rightone)==0){
                x ^=n;
            }
            else y^=n;
        }

        cout<<x<<" "<<y<<endl;
        //现在x, y是其中一个数字，需要确定那个是重复哪个是缺失
        vector<int> res={y,x};
        for(int& n:nums){
            if(n==x) res={x,y};
        }
        return res;


    }
};

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }
        for (int i = 1; i <= n; i++) {
            xorSum ^= i;
        }
        int lowbit = xorSum & (-xorSum);
        int num1 = 0, num2 = 0;
        for (int &num : nums) {
            if ((num & lowbit) == 0) {
                num1 ^= num;
            } else {
                num2 ^= num;
            }
        }
        for (int i = 1; i <= n; i++) {
            if ((i & lowbit) == 0) {
                num1 ^= i;
            } else {
                num2 ^= i;
            }
        }
        for (int num : nums) {
            if (num == num1) {
                return vector<int>{num1, num2};
            }
        }
        return vector<int>{num2, num1};
    }
};


// @lc code=end

