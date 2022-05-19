/*
 * @lc app=leetcode.cn id=174 lang=cpp
 *
 * [174] 地下城游戏
 *
 * https://leetcode-cn.com/problems/dungeon-game/description/
 *
 * algorithms
 * Hard (48.37%)
 * Likes:    616
 * Dislikes: 0
 * Total Accepted:    48.1K
 * Total Submissions: 99.6K
 * Testcase Example:  '[[-2,-3,3],[-5,-10,1],[10,30,-5]]'
 *
 * 
 * table.dungeon, .dungeon th, .dungeon td {
 * ⁠ border:3px solid black;
 * }
 * 
 * ⁠.dungeon th, .dungeon td {
 * ⁠   text-align: center;
 * ⁠   height: 70px;
 * ⁠   width: 70px;
 * }
 * 
 * 
 * 一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N
 * 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。
 * 
 * 骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。
 * 
 * 有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为
 * 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。
 * 
 * 为了尽快到达公主，骑士决定每次只向右或向下移动一步。
 * 
 * 
 * 
 * 编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。
 * 
 * 例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。
 * 
 * 
 * ⁠
 * -2 (K) 
 * -3 
 * 3 
 * ⁠
 * ⁠
 * -5 
 * -10 
 * 1 
 * ⁠
 * ⁠
 * 10 
 * 30 
 * -5 (P) 
 * ⁠
 * 
 * 
 * 
 * 
 * 
 * 说明:
 * 
 * 
 * 
 * 骑士的健康点数没有上限。
 * 
 * 任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// class Solution {
// public:
//     int calculateMinimumHP(vector<vector<int>>& dungeon) {
//         int r=dungeon.size();
//         int c = dungeon[0].size();
//         vector<vector<int>> dp(r,vector<int>(c));
//         dp[r-1][c-1] = dungeon[r-1][c-1]<=0? 1-dungeon[r-1][c-1]:1;
//         for(int i=c-2;i>=0;i--){
//             dp[r-1][i] = dp[r-1][i+1] -dungeon[r-1][i];
//             if(dp[r-1][i]<=0) dp[r-1][i]=1;
//         }
//         for(int i=r-2;i>=0;i--){
//             for(int j=c-1;j>=0;j--){
//                 // cout<<i<<" "<<j<<endl;
//                 if(j==c-1) {
//                     dp[i][j] = dp[i+1][j] -dungeon[i][j];
//                     if(dp[i][j]<=0) dp[i][j]=1;
//                     continue;
//                 }
//                 dp[i][j] = min(dp[i+1][j],dp[i][j+1]) - dungeon[i][j];
//                 if(dp[i][j]<=0) dp[i][j]=1;
//             }
//         }
//         return dp[0][0]>0?dp[0][0]:1;
//     }
// };

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int r=dungeon.size();
        int c = dungeon[0].size();

        vector<int>dp(c);
        dp[c-1] = dungeon[r-1][c-1]<=0? 1-dungeon[r-1][c-1]:1;

        for(int i=c-2;i>=0;i--){
            dp[i] = dp[i+1] -dungeon[r-1][i];
            if(dp[i]<=0) dp[i]=1;
        }
        for(int i=r-2;i>=0;i--){
            dp[c-1] = dp[c-1] - dungeon[i][c-1];
            if(dp[c-1]<=0) dp[c-1]=1;
            for(int j=c-2;j>=0;j--){
                dp[j] = min(dp[j],dp[j+1]) - dungeon[i][j];
                if(dp[j]<=0) dp[j]=1;
            }
        }
        return dp[0]>0?dp[0]:1;
    }
};
// @lc code=end

