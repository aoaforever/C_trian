/*
 * @lc app=leetcode.cn id=354 lang=cpp
 *
 * [354] 俄罗斯套娃信封问题
 *
 * https://leetcode-cn.com/problems/russian-doll-envelopes/description/
 *
 * algorithms
 * Hard (42.51%)
 * Likes:    725
 * Dislikes: 0
 * Total Accepted:    84.6K
 * Total Submissions: 200K
 * Testcase Example:  '[[5,4],[6,4],[6,7],[2,3]]'
 *
 * 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
 * 
 * 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
 * 
 * 请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
 * 
 * 注意：不允许旋转信封。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * 输出：3
 * 解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
 * 
 * 示例 2：
 * 
 * 
 * 输入：envelopes = [[1,1],[1,1],[1,1]]
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= envelopes.length <= 10^5
 * envelopes[i].length == 2
 * 1 <= wi, hi <= 10^5
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
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        vector<int> dp(envelopes.size(),1);
        sort(envelopes.begin(),envelopes.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]) return a[1] < b[1];//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            return a[0]<b[0];
        });
        for(int i=1;i<envelopes.size();i++){
            for(int j=i-1;j>=0;j--){
                if(envelopes[i][0]>envelopes[j][0]){
                    if(envelopes[i][1]>envelopes[j][1]){
                        dp[i] = max(dp[i],dp[j]+1);
                    }
                }
                
            }   
        }
        int res=-2;
        for(int i=0;i<dp.size();i++){
            res = max(res,dp[i]);
        }
        return res;
    }
};
// @lc code=end

