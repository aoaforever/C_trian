/*
 * @lc app=leetcode.cn id=887 lang=cpp
 *
 * [887] 鸡蛋掉落
 *
 * https://leetcode-cn.com/problems/super-egg-drop/description/
 *
 * algorithms
 * Hard (29.65%)
 * Likes:    817
 * Dislikes: 0
 * Total Accepted:    63.7K
 * Total Submissions: 214.2K
 * Testcase Example:  '1\n2'
 *
 * 给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。
 * 
 * 已知存在楼层 f ，满足 0  ，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。
 * 
 * 每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1
 * ）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。
 * 
 * 请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：k = 1, n = 2
 * 输出：2
 * 解释：
 * 鸡蛋从 1 楼掉落。如果它碎了，肯定能得出 f = 0 。 
 * 否则，鸡蛋从 2 楼掉落。如果它碎了，肯定能得出 f = 1 。 
 * 如果它没碎，那么肯定能得出 f = 2 。 
 * 因此，在最坏的情况下我们需要移动 2 次以确定 f 是多少。 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：k = 2, n = 6
 * 输出：3
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：k = 3, n = 14
 * 输出：4
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
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
    vector<vector<int>> memo;
    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k+1,vector<int>(n+1,-1));
        return dp(k,n);
    }
    int dp(int k, int end){
        if(end==0) return 0;
        if(k==1) return end;

        if(memo[k][end]!=-1) return memo[k][end];
        int res =INT_MAX;
        for(int i=1;i<=end;i++){
            res =min(
                max(
                    dp(k-1,i-1),
                    dp(k,end-i)
                )+1,res
            );
        }
        memo[k][end] = res;
        return res;
    }
};
// @lc code=end

