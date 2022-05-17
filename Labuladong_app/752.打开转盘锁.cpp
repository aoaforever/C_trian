/*
 * @lc app=leetcode.cn id=752 lang=cpp
 *
 * [752] 打开转盘锁
 *
 * https://leetcode-cn.com/problems/open-the-lock/description/
 *
 * algorithms
 * Medium (52.99%)
 * Likes:    488
 * Dislikes: 0
 * Total Accepted:    90.9K
 * Total Submissions: 171.4K
 * Testcase Example:  '["0201","0101","0102","1212","2002"]\n"0202"'
 *
 * 你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8',
 * '9' 。每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
 * 
 * 锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
 * 
 * 列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
 * 
 * 字符串 target 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1 。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 * 输出：6
 * 解释：
 * 可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
 * 注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
 * 因为当拨动到 "0102" 时这个锁就会被锁定。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: deadends = ["8888"], target = "0009"
 * 输出：1
 * 解释：把最后一位反向旋转一次即可 "0000" -> "0009"。
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"],
 * target = "8888"
 * 输出：-1
 * 解释：无法旋转到目标数字且不被锁定。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= deadends.length <= 500
 * deadends[i].length == 4
 * target.length == 4
 * target 不在 deadends 之中
 * target 和 deadends[i] 仅由若干位数字组成
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        //上转、下转、不转
        //从0000开始为第一层，则下一层有
        //每次只能旋转一个拨轮，而不是一次性拨4个位置
        queue<string> q;
        set<string> ss;
        set<string> dead;
        for(string& d:deadends){
            dead.insert(d);
        }

        q.push("0000");
        ss.insert("0000");
        int step =0;
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;i++){

                string s = q.front();
                q.pop();
                if(s == target) return step;
                if(dead.count(s)) continue;
                //每个位置都有两种情况
                for(int i=0;i<4;i++){
                    //加一
                    string add =addone(s,i);
                    if(!ss.count(add)) {
                        q.push(add);
                        ss.insert(add);
                        }

                    //减一
                    string minus_ = minusone(s,i);
                    if(!ss.count(minus_)){
                        q.push(minus_); 
                        ss.insert(minus_);
                    }
                }
                
            }
            //注意step的位置啊，是外层for，也就是这一层遍历完在加深度，
            step++;
        }
        return -1;
    }
    string addone(string s, int i){
        if(s[i]=='9') {
            s[i]='0';
            return s;
        }
        s[i]++;
        return s;
    }
    string minusone(string s, int i){
        if(s[i]=='0') {
            s[i]='9';
            return s;
        }
        s[i]--;
        return s;
    }
};
// @lc code=end

