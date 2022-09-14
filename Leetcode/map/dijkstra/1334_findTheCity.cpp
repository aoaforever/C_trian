#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <list>
using namespace std;
class Solution {
public:
    class State{
        public:
        int id;
        int distfromstart;
        bool operator<(const State& a) const {
            return this->distfromstart > a.distfromstart;//降序，但是是小根堆
        }
        State(int id_, int dist_){
            id = id_;
            distfromstart = dist_;
        }
    };
    int m;//节点总数
    vector<int> dijkstra(vector<list<pair<int,int>>>& graph, int start){
        vector<int> res(m,INT_MAX);
        res[start] = 0;//自己到自己肯定是0距离

        priority_queue<State> q;
        q.emplace(start,0);
        while(!q.empty()){
            State s = q.top();
            q.pop();

            int cur_id = s.id;
            int cur_dist = s.distfromstart;

            if(cur_dist>res[cur_id]) continue;

            for(auto g:graph[cur_id]){
                int next_id = g.first;
                int next_dist = g.second;
                int next_distfromstart = cur_dist + next_dist;
                if(next_distfromstart<res[next_id]){
                    q.emplace(next_id,next_distfromstart);
                    res[next_id] = next_distfromstart;
                }
            }
        }
        return res;
    }
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        m = n;
        vector<list<pair<int,int>>> graph(n);//必须初始化空间！！！！！！！！！！！
        for(auto e:edges){
            int from = e[0];
            int to =e[1];
            int dist = e[2];

            graph[from].emplace_back(to,dist);//对于无向图，必须两个方向都设置！！！！！！
            graph[to].emplace_back(from,dist);
        }

        int ans_size=INT_MAX,ans_index;
        for(int i=0;i<n;i++){
            vector<int> res = dijkstra(graph,i);//每次返回一个从i到所有节点的数组
            int size =0;
            for(int j=0;j<res.size();j++){
                // cout<<"城市"<<i<<"到"<<j<<"的距离为"<<res[j]<<endl;
                if(j!=i&& res[j]<=distanceThreshold){
                    size++;
                }
            }
            // cout<<"城市"<<i<<"的邻居城市有"<<size<<"个"<<endl;
            if(size<=ans_size){
                ans_size = size;
                ans_index = i;
            }
        }
        return ans_index;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    vector<vector<int>> edges{{0,1,3},{1,2,1},{1,3,4},{2,3,1}};

    cout<<s.findTheCity(4,edges,4)<<endl;;
    return 0;
}
