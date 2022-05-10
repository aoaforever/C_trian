/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 *
 * https://leetcode-cn.com/problems/course-schedule/description/
 *
 * algorithms
 * Medium (53.85%)
 * Likes:    1256
 * Dislikes: 0
 * Total Accepted:    204.5K
 * Total Submissions: 379.8K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
 * 
 * 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi]
 * ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
 * 
 * 
 * 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
 * 
 * 
 * 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：numCourses = 2, prerequisites = [[1,0]]
 * 输出：true
 * 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
 * 
 * 示例 2：
 * 
 * 
 * 输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
 * 输出：false
 * 解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * prerequisites[i].length == 2
 * 0 i, bi < numCourses
 * prerequisites[i] 中的所有课程对 互不相同
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
#include <list>
using namespace std;
class Solution {
public:
    vector<bool> visited;
    vector<bool> onPath;
    bool hasCycle = false;

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        vector<list<int>> graph=buildGraph(numCourses,prerequisites);
        visited = vector<bool>(numCourses);
        onPath = vector<bool>(numCourses);
        for(int i=0;i<numCourses;i++){
            traverse(graph,i);
        }
        return !hasCycle;
    }
    void traverse(vector<list<int>>& graph,int s){
        if(onPath[s]){
            //发现环
            hasCycle = true;
        }
        if(visited[s]||hasCycle) return;
        //将节点s标记为已遍历
        visited[s] = true;
        //开始遍历节点s
        onPath[s] = true;
        for(int t: graph[s]){
            traverse(graph,t);
        }
        //节点s遍历完成
        onPath[s] = false;
    }
    vector<list<int>> buildGraph(int numCourses,vector<vector<int>>& prerequisites){
        //图中共有numCourses个节点
        vector<list<int>> graph = vector<list<int>>(numCourses);
        for(vector<int> &edge: prerequisites){
            int from = edge[1];
            int to = edge[0];
            //要修完课程from 才能修课程to
            //在图中添加一条从from指向to的有向边
            graph[from].push_back(to);
        }
        return graph;
    }
};
// @lc code=end

