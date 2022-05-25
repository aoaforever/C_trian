/*
 * @lc app=leetcode.cn id=204 lang=cpp
 *
 * [204] 计数质数
 *
 * https://leetcode-cn.com/problems/count-primes/description/
 *
 * algorithms
 * Medium (37.51%)
 * Likes:    892
 * Dislikes: 0
 * Total Accepted:    204K
 * Total Submissions: 543.7K
 * Testcase Example:  '10'
 *
 * 给定整数 n ，返回 所有小于非负整数 n 的质数的数量 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 10
 * 输出：4
 * 解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 0
 * 输出：0
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 1
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= n <= 5 * 10^6
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

    int countPrimes(int n) {
        vector<bool> res(n,true);

        for(int i=2;i<n;i=i+1){
            if(res[i]){
                //如果i是素数，那么它的倍数肯定都不是素数
                for(int j=i*2;j<n;j=j+i){
                    res[j] =false;
                }
            }
        }
        int sum=0;
        for(int i=2;i<n;i++){
            if(res[i]) sum++;
        }
        return sum;
    }
};
// @lc code=end

