/*
 * @lc app=leetcode.cn id=1514 lang=cpp
 *
 * [1514] 概率最大的路径
 *
 * https://leetcode.cn/problems/path-with-maximum-probability/description/
 *
 * algorithms
 * Medium (36.73%)
 * Likes:    105
 * Dislikes: 0
 * Total Accepted:    12.8K
 * Total Submissions: 34.5K
 * Testcase Example:  '3\n[[0,1],[1,2],[0,2]]\n[0.5,0.5,0.2]\n0\n2'
 *
 * 给你一个由 n 个节点（下标从 0 开始）组成的无向加权图，该图由一个描述边的列表组成，其中 edges[i] = [a, b] 表示连接节点 a 和
 * b 的一条无向边，且该边遍历成功的概率为 succProb[i] 。
 * 
 * 指定两个节点分别作为起点 start 和终点 end ，请你找出从起点到终点成功概率最大的路径，并返回其成功概率。
 * 
 * 如果不存在从 start 到 end 的路径，请 返回 0 。只要答案与标准答案的误差不超过 1e-5 ，就会被视作正确答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0,
 * end = 2
 * 输出：0.25000
 * 解释：从起点到终点有两条路径，其中一条的成功概率为 0.2 ，而另一条为 0.5 * 0.5 = 0.25
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0,
 * end = 2
 * 输出：0.30000
 * 
 * 
 * 示例 3：
 * 
 * 
 * 
 * 输入：n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
 * 输出：0.00000
 * 解释：节点 0 和 节点 2 之间不存在路径
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= n <= 10^4
 * 0 <= start, end < n
 * start != end
 * 0 <= a, b < n
 * a != b
 * 0 <= succProb.length == edges.length <= 2*10^4
 * 0 <= succProb[i] <= 1
 * 每两个节点之间最多有一条边
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;
class Solution {
public:
    class State{
        public:
            int id;
            double probFromStart;
            State(int id,double prob){
                this->id=id;
                probFromStart = prob;
            }
            friend bool operator<(const State& a, const State&b) {
                return a.probFromStart<b.probFromStart;//大根堆
            }
    };
    int n;
    vector<list<pair<int,double>>> graph;
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        this->n=n;
        graph.resize(n);
        cout<<graph.size()<<endl;
        for(int i=0;i<edges.size();i++){
            cout<<i<<endl;
            int node1 = edges[i][0];
            int node2 = edges[i][1];
            double prob = succProb[i];
            graph[node1].push_back({node2,prob});
            graph[node2].push_back({node1,prob});
        }
        return dijkstra(start,end);
    }

    
    double dijkstra(int start,int end){
        vector<double> prob(n,0);
        prob[start] = 1.0;
        priority_queue<State> q;
        q.emplace(start,1.0);
        cout<<q.size()<<endl;
        while(!q.empty()){
            State curNode = q.top();
            q.pop();

            int curid = curNode.id;
            double curProb = curNode.probFromStart;
            cout<<curid<<"  "<<curProb<<endl;
            if(curid == end){
                return curProb;
            }
            if(curProb<prob[curid]) continue;

            for(auto& neiborh:graph[curid]){
                int nextId = neiborh.first;
                double nextprob = neiborh.second * curProb;

                if(nextprob>prob[nextId]){
                    prob[nextId] = nextprob;
                    q.emplace(nextId,nextprob);
                }
            }

        }
        return 0;

    }
};
// @lc code=end

