/*
 * @lc app=leetcode.cn id=1631 lang=cpp
 *
 * [1631] 最小体力消耗路径
 *
 * https://leetcode.cn/problems/path-with-minimum-effort/description/
 *
 * algorithms
 * Medium (49.97%)
 * Likes:    293
 * Dislikes: 0
 * Total Accepted:    32.6K
 * Total Submissions: 65K
 * Testcase Example:  '[[1,2,2],[3,8,2],[5,3,5]]'
 *
 * 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子
 * (row, col) 的高度。一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从
 * 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。
 * 
 * 一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。
 * 
 * 请你返回从左上角走到右下角的最小 体力消耗值 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：heights = [[1,2,2],[3,8,2],[5,3,5]]
 * 输出：2
 * 解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
 * 这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：heights = [[1,2,3],[3,8,4],[5,3,5]]
 * 输出：1
 * 解释：路径 [1,2,3,4,5] 的相邻格子差值绝对值最大为 1 ，比路径 [1,3,5,3,5] 更优。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
 * 输出：0
 * 解释：上图所示路径不需要消耗任何体力。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * rows == heights.length
 * columns == heights[i].length
 * 1 
 * 1 
 * 
 * 
 */

// @lc code=start




#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
class Solution {
public:
    class State{
        public:
            int x,y;
            int distFromStart;
            State(int _x,int _y,int dist):x(_x),y(_y),distFromStart(dist){};

            bool operator<(const State&b) const{
                return this->distFromStart>b.distFromStart;
            }
    };
    int r,c;
    int minimumEffortPath(vector<vector<int>>& heights) {
        r=heights.size();
        c=heights[0].size();
        cout<<r<<" "<<c<<endl;
        int res =dijkstra(0,0,heights);
        
        return res;
    }
    vector<vector<int>> dir{
        {-1,0},{1,0},{0,-1},{0,1}
    };

    vector<vector<int>> adj(int x,int y){
        //给定x,y，求出临近节点
        vector<vector<int>> res;
        for(auto &d :dir){
            int newx = x+d[0];
            int newy = y+d[1];
            if(newx<0||newx>=r||newy<0||newy>=c) continue;
            res.emplace_back(vector<int>{newx,newy});
        }
        return res;
    }

    int dijkstra(int x,int y,vector<vector<int>>& heights){
        vector<vector<int>> effortTo(r,vector<int>(c,INT_MAX));
        effortTo[0][0] =0;
        priority_queue<State> pq;
        pq.emplace(x,y,0);

        while(!pq.empty()){

            State curNode = pq.top();
            pq.pop();
            int curX = curNode.x;
            int curY = curNode.y;
            int curDistfromStart = curNode.distFromStart;
            cout<<curX<<","<<curY<<"   "<<curDistfromStart<<endl;
            if((curX==(r-1))&&(curY==(c-1))){
                return curDistfromStart;
            }

            if(curDistfromStart>effortTo[curX][curY]) continue;

            for(auto& neibor:adj(curX,curY)){
                int nextX = neibor[0];
                int nextY = neibor[1];
                
                int nextDist = max(
                    effortTo[curX][curY],
                abs(heights[curX][curY]-heights[nextX][nextY])
                );
                if(nextDist<effortTo[nextX][nextY]){
                    pq.emplace(nextX,nextY,nextDist);
                    effortTo[nextX][nextY] = nextDist;
                }
            }
            
        }
        return -1;
    }
};
// @lc code=end


class Solution {
public:
    class State{
        public:
            int x,y;
            int distFromStart;
            State(int _x,int _y,int dist):x(_x),y(_y),distFromStart(dist){};

            bool operator<(const State&b) const{
                return this->distFromStart>b.distFromStart;
            }
    };
    vector<vector<int>> dir{
        {-1,0},{1,0},{0,-1},{0,1}
    };
    int r,c;
    int minimumEffortPath(vector<vector<int>>& heights) {
        r=heights.size();
        c=heights[0].size();
        cout<<r<<" "<<c<<endl;
        
        vector<vector<int>> effortTo(r,vector<int>(c,INT_MAX));
        effortTo[0][0] =0;
        priority_queue<State> pq;
        pq.emplace(0,0,0);
        vector<int> seen(r*c,0);
        
        while(!pq.empty()){

            auto curNode = pq.top();
            pq.pop();
            int curX = curNode.x;
            int curY = curNode.y;
            int curDistfromStart = curNode.distFromStart;
            cout<<curX<<","<<curY<<"   "<<curDistfromStart<<endl;

            if(seen[curX*c+curY]==1) continue;

            if((curX==(r-1))&&(curY==(c-1))){
                break;
            }
            seen[curX*c+curY]=1;

            if(curDistfromStart>effortTo[curX][curY]) continue;
            for(int i=0;i<4;i++){
                vector<int>& d = dir[i];
                int nx = curX + d[0];
                int ny = curY + d[1];
                if(nx>=0&&nx<r&&ny>=0&&ny<c){
                    if(seen[nx*c+ny]!=1){
                        int nd = max(abs(heights[nx][ny]-heights[curX][curY]),
                            effortTo[curX][curY]
                            );
                        if(nd<effortTo[nx][ny]){
                            effortTo[nx][ny]=nd;
                            pq.emplace(nx,ny,nd);
                        }
                        
                    }
                }
            }
            
        }
       
        
        return effortTo[r-1][c-1];
    }
};