/*
 * @lc app=leetcode.cn id=793 lang=cpp
 *
 * [793] 阶乘函数后 K 个零
 *
 * https://leetcode-cn.com/problems/preimage-size-of-factorial-zeroes-function/description/
 *
 * algorithms
 * Hard (40.31%)
 * Likes:    88
 * Dislikes: 0
 * Total Accepted:    7.9K
 * Total Submissions: 19.5K
 * Testcase Example:  '0'
 *
 *  f(x) 是 x! 末尾是 0 的数量。回想一下 x! = 1 * 2 * 3 * ... * x，且 0! = 1 。
 * 
 * 
 * 例如， f(3) = 0 ，因为 3! = 6 的末尾没有 0 ；而 f(11) = 2 ，因为 11!= 39916800 末端有 2 个 0 。
 * 
 * 
 * 给定 k，找出返回能满足 f(x) = k 的非负整数 x 的数量。
 * 
 * 
 * 
 * 示例 1： 
 * 
 * 
 * 输入：k = 0
 * 输出：5
 * 解释：0!, 1!, 2!, 3!, 和 4! 均符合 k = 0 的条件。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：k = 5
 * 输出：0
 * 解释：没有匹配到这样的 x!，符合 k = 5 的条件。
 * 
 * 示例 3:
 * 
 * 
 * 输入: k = 3
 * 输出: 5
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 0 <= k <= 10^9
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int preimageSizeFZF(int k) {
        //k是末尾0的数量， 自变量是x，x越大，f(x)的数量就越多
        //如果你要尾部数量高达10^9，那么x的类型就得是long long 
        //因此，找左界 和 右界
        long left = left_bound(k);
        long right = right_bound(k);
        return int(right-left+1);

    }
    long left_bound(int target){
        long long left=0, right = LLONG_MAX;
        while (left<right)
        {
            long long mid = left +(right-left)/2;
            long res = trailingZeroes(mid);
            if(res<target){
                left = mid+1;
            }
            else if(res>target){
                right =mid;
            }
            else{
                //左界  
                right =mid;//左闭右开
            }
        }
        return right;
        
    }
    long right_bound(int target){
        long long left=0, right = LLONG_MAX;
        while (left<right)
        {
            long long mid = left +(right-left)/2;
            long res = trailingZeroes(mid);
            if(res<target){
                left = mid+1;
            }
            else if(res>target){
                right =mid;
            }
            else{
                //右界  
                left = mid+1;//左闭右开
            }
        }
        return left-1;
        
    }

    long trailingZeroes(long long n) {
        long res=0;
        for(;n>0;n=n/5){
            res += n/5;

        }
        return res;
    }
};
// @lc code=end

