/*
 * @lc app=leetcode.cn id=743 lang=cpp
 *
 * [743] 网络延迟时间
 *
 * https://leetcode-cn.com/problems/network-delay-time/description/
 *
 * algorithms
 * Medium (54.00%)
 * Likes:    551
 * Dislikes: 0
 * Total Accepted:    79.8K
 * Total Submissions: 147.1K
 * Testcase Example:  '[[2,1,1],[2,3,1],[3,4,1]]\n4\n2'
 *
 * 有 n 个网络节点，标记为 1 到 n。
 * 
 * 给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点，
 * wi 是一个信号从源节点传递到目标节点的时间。
 * 
 * 现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：times = [[1,2,1]], n = 2, k = 1
 * 输出：1
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：times = [[1,2,1]], n = 2, k = 2
 * 输出：-1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= k <= n <= 100
 * 1 <= times.length <= 6000
 * times[i].length == 3
 * 1 <= ui, vi <= n
 * ui != vi
 * 0 <= wi <= 100
 * 所有 (ui, vi) 对都 互不相同（即，不含重复边）
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <list>
#include <queue>
using namespace std;
// class Solution {
// public:
//     class State{
//     public:
//         int id;
//         //从start节点到当前节点的距离，也就是深度
//         int distFromStart;
//         State(int id,int distFromStart){
//             this->id = id;
//             this->distFromStart = distFromStart;
//         };
//         friend bool operator<(State& a, State& b){
//             return a.distFromStart<b.distFromStart;
//         }
        
//     };

//     //需要构建邻接表
//     vector<list<vector<int>>> graph;
//     int networkDelayTime(vector<vector<int>>& times, int n, int k) {
//         graph = vector<list<vector<int>>>(n+1);//因为从1开始编号
//         for(vector<int>& t:times){
//             int from = t[0];
//             int to = t[1];
//             int weight = t[2];
//             graph[from].push_back({to,weight});
//         }
//         vector<int> distTo = dijkstra(k);

//         //找到最长的那一条最短路径
//         int res=0;
//         for(int i=1;i<distTo.size();i++){
//             if(distTo[i]==INT_MAX) return -1;
//             res = max(res, distTo[i]);
//         }
//         return res;
//     }
//     vector<int> dijkstra(int start){
//         //定义，distTo[i]的值就是起点start到节点i的最短路径权重
//         vector<int> distTo(graph.size(),INT_MAX);
//         distTo[start] =0;

//         priority_queue<State*> pq;
//         pq.push(new State(start,0));
//         while (!pq.empty())
//         {
//             int sz= pq.size();
//             for(int i=0;i<sz;i++){
//                 State* s = pq.top();
//                 pq.pop();

//                 int curNodeId = s->id;
//                 int curDistFromStart = s->distFromStart;

//                 //distTo[curNodeId] 相当于如果memo[]已经存在，则直接return
//                 //由于是贪心，所以如果之前已经算出了更优的结果，那么
//                 //注意不能是=
//                 if(curDistFromStart>distTo[curNodeId]) continue;

//                 for(auto& neighbor:graph[curNodeId]){
//                     int nextId = neighbor[0];
//                     int distToNextNode = neighbor[1]+distTo[curNodeId];

//                     //更新dp table
//                     if(distTo[nextId] > distToNextNode){
//                         distTo[nextId] = distToNextNode;
//                         pq.push(new State(nextId,distToNextNode));//会有重复的id，但是路径长度可能不同
//                     }
//                 }

//             }
//         }
//         return distTo;
//     }
// };
// // @lc code=end


class Solution {
public:
        struct state{
            int id;
            int distfromstart;
            state(int id, int dist):id(id),distfromstart(dist){};

            bool operator<(const state& b) const {
                return this->distfromstart>b.distfromstart;
            }
        };
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {



        vector<list<pair<int,int>>> graph;

        for(vector<int>& t:times){
            // auto [from,to,dist] = t;
            int from=t[0];
            int to = t[1];
            int dist = t[2];
            graph[from].emplace_back(to,dist);

        }

        vector<int> d = dijkstra(graph,k,n);
        int m=INT_MAX;
        for(int& a:d){
            m = min(m,a);
            if(a==INT_MAX) return -1;
        }
        return m;
    }

    vector<int> dijkstra(vector<list<pair<int,int>>> &graph, int k,int n){
        vector<int> res(graph.size(),INT_MAX);
        res[k]=0;

        priority_queue<state> q;
        q.emplace(k,0);

        while(!q.empty()){
            state s = q.top();
            q.pop();

            if(res[s.id]<s.distfromstart){
                continue;
            }

            for(pair<int,int>& g:graph[s.id]){
                // auto [to,dist] = g;
                int to = g.first;
                int dist = g.second;
                int nextdist = s.distfromstart+dist;
                if(nextdist<res[to]){
                    res[to] = nextdist;
                    q.emplace(to,nextdist);
                }
                
            }
        }
        return res;

    }
};