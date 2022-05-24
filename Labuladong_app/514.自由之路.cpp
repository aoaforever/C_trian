/*
 * @lc app=leetcode.cn id=514 lang=cpp
 *
 * [514] 自由之路
 *
 * https://leetcode-cn.com/problems/freedom-trail/description/
 *
 * algorithms
 * Hard (50.28%)
 * Likes:    239
 * Dislikes: 0
 * Total Accepted:    22.6K
 * Total Submissions: 44.9K
 * Testcase Example:  '"godding"\n"gd"'
 *
 * 电子游戏“辐射4”中，任务 “通向自由” 要求玩家到达名为 “Freedom Trail Ring” 的金属表盘，并使用表盘拼写特定关键词才能开门。
 * 
 * 给定一个字符串 ring ，表示刻在外环上的编码；给定另一个字符串 key ，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。
 * 
 * 最初，ring 的第一个字符与 12:00 方向对齐。您需要顺时针或逆时针旋转 ring 以使 key 的一个字符在 12:00
 * 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符。
 * 
 * 旋转 ring 拼出 key 字符 key[i] 的阶段中：
 * 
 * 
 * 您可以将 ring 顺时针或逆时针旋转 一个位置 ，计为1步。旋转的最终目的是将字符串 ring 的一个字符与 12:00
 * 方向对齐，并且这个字符必须等于字符 key[i] 。
 * 如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1 步。按完之后，您可以开始拼写 key
 * 的下一个字符（下一阶段）, 直至完成所有拼写。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 
 * 
 * 输入: ring = "godding", key = "gd"
 * 输出: 4
 * 解释:
 * ⁠对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。 
 * ⁠对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"。
 * ⁠当然, 我们还需要1步进行拼写。
 * ⁠因此最终的输出是 4。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: ring = "godding", key = "godding"
 * 输出: 13
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= ring.length, key.length <= 100
 * ring 和 key 只包含小写英文字母
 * 保证 字符串 key 一定可以由字符串  ring 旋转拼出
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<char,vector<int>> charToindex;
    unordered_map<string,int> memo;
    int findRotateSteps(string ring, string key) {
        for(int i=0;i<ring.size();i++){
            charToindex[ring[i]].push_back(i);
        }
        return dp(ring,0,key,0);
    }
    int dp(string& ring, int i, string & key , int j){
        //我现在在i，和j，转动到key[j]的最少次数
        //但是，i到key[j]可能有多条路径
        //那么就每条路径都算出来，取最小值

        //为了避免每次递归都去调用函数找位置，直接用一个哈希表记录所有字母的位置
        if(j==key.size()) return 0;//是0不是1 ，已经找完了，不需要再转了
        
        string a = to_string(i)+" "+to_string(j);
        if(memo.count(a)) return memo[a];
        int n = ring.size();
        char target = key[j];
        int res=INT_MAX;


        for(auto k : charToindex[target]){
            //穷举所有的位置，取最小值
            // int left = k+ring.size()-i;//往左转的步数
            // int right = i-k; //往右转的步数
            // int step = min(left,right);

            int delta = abs(i-k);//是一个环，所以只能用这种情况
            int step = min(delta,n-delta);

            int subproblem = dp(ring,k,key,j+1);
            res = min(res, subproblem+step+1);
        }

        memo[a] = res;
        return res;
    }
};
// @lc code=end

