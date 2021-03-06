/*
 * @lc app=leetcode.cn id=773 lang=cpp
 *
 * [773] 滑动谜题
 *
 * https://leetcode-cn.com/problems/sliding-puzzle/description/
 *
 * algorithms
 * Hard (70.64%)
 * Likes:    258
 * Dislikes: 0
 * Total Accepted:    27.6K
 * Total Submissions: 39.1K
 * Testcase Example:  '[[1,2,3],[4,0,5]]'
 *
 * 在一个 2 x 3 的板上（board）有 5 块砖瓦，用数字 1~5 来表示, 以及一块空缺用 0 来表示。一次 移动 定义为选择 0
 * 与一个相邻的数字（上下左右）进行交换.
 * 
 * 最终当板 board 的结果是 [[1,2,3],[4,5,0]] 谜板被解开。
 * 
 * 给出一个谜板的初始状态 board ，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：board = [[1,2,3],[4,0,5]]
 * 输出：1
 * 解释：交换 0 和 5 ，1 步完成
 * 
 * 
 * 示例 2:
 * 
 * 
 * 
 * 
 * 输入：board = [[1,2,3],[5,4,0]]
 * 输出：-1
 * 解释：没有办法完成谜板
 * 
 * 
 * 示例 3:
 * 
 * 
 * 
 * 
 * 输入：board = [[4,1,2],[5,0,3]]
 * 输出：5
 * 解释：
 * 最少完成谜板的最少移动次数是 5 ，
 * 一种移动路径:
 * 尚未移动: [[4,1,2],[5,0,3]]
 * 移动 1 次: [[4,1,2],[0,5,3]]
 * 移动 2 次: [[0,1,2],[4,5,3]]
 * 移动 3 次: [[1,0,2],[4,5,3]]
 * 移动 4 次: [[1,2,0],[4,5,3]]
 * 移动 5 次: [[1,2,3],[4,5,0]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * board.length == 2
 * board[i].length == 3
 * 0 <= board[i][j] <= 5
 * board[i][j] 中每个值都 不同
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <set>
using namespace std;
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target ="123450";
        string sb="";
        for(auto& b:board){
            for(auto& i:b){
                sb+=to_string(i);
            }
        }
        cout<<sb<<endl;
        vector<vector<int>> dir{
            {1,3},
            {0,2,4},
            {1,5},
            {0,4},
            {1,3,5},
            {2,4}
        };
        set<string> used;
        queue<string> q;
        q.push(sb);
        used.insert(sb);
        int step=0;
        while(!q.empty()){
            int sz=q.size();
            for(int i=0;i<sz;i++){
                string tmp = q.front();
                q.pop();
                int index = tmp.find('0');
                cout<<index<<endl;
                if(tmp==target) return step;     
                for(int& d:dir[index]){
                    //和dd位置交换
                    string t = tmp;
                    swap(t[index],t[d]);
                    if(used.count(t)){
                        continue;
                    }
                    used.insert(t);
                    q.push(t);
                    
                }
            }
            step++;
        }
        return -1;

    }
};
// @lc code=end

