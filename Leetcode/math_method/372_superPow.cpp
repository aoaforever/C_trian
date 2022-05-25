/*
 * @lc app=leetcode.cn id=372 lang=cpp
 *
 * [372] 超级次方
 *
 * https://leetcode-cn.com/problems/super-pow/description/
 *
 * algorithms
 * Medium (57.32%)
 * Likes:    271
 * Dislikes: 0
 * Total Accepted:    39.4K
 * Total Submissions: 68.7K
 * Testcase Example:  '2\n[3]'
 *
 * 你的任务是计算 a^b 对 1337 取模，a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：a = 2, b = [3]
 * 输出：8
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：a = 2, b = [1,0]
 * 输出：1024
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：a = 1, b = [4,3,3,8,5,2]
 * 输出：1
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：a = 2147483647, b = [2,0,0]
 * 输出：1198
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 0 
 * b 不含前导 0
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
    // a^[1,2,3,4] = a^4* (a^[1,2,3])^10
    //(a*b)%k = (a%k)(b%k)%k
    int mypow(int a, int k){
        a = a%1337;
        int res=1;
        for(int _=0;_<k;_++){
            res = res*a;
            res = res%1337;
        }
        return res;
    }
    int superPow(int a, vector<int>& b) {
        if(b.size()==0) return 1;
        int last = b.back();
        b.pop_back();
        int part1 = mypow(a,last);
        int part2 = mypow(superPow(a,b),10);
        return (part1*part2)%1337;
    }

};
// @lc code=end

