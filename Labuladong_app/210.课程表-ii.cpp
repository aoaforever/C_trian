/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 *
 * https://leetcode-cn.com/problems/course-schedule-ii/description/
 *
 * algorithms
 * Medium (55.48%)
 * Likes:    617
 * Dislikes: 0
 * Total Accepted:    125.4K
 * Total Submissions: 226K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中
 * prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。
 * 
 * 
 * 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
 * 
 * 
 * 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：numCourses = 2, prerequisites = [[1,0]]
 * 输出：[0,1]
 * 解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * 输出：[0,2,1,3]
 * 解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
 * 因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
 * 
 * 示例 3：
 * 
 * 
 * 输入：numCourses = 1, prerequisites = []
 * 输出：[0]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= numCourses <= 2000
 * 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * prerequisites[i].length == 2
 * 0 <= ai, bi < numCourses
 * ai != bi
 * 所有[ai, bi] 互不相同
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
    vector<int> postorder;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    
        if(!canFinish(numCourses,prerequisites)){
            return {};
        }
        reverse(postorder.begin(),postorder.end());
        return postorder;
    }

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
        postorder.push_back(s);
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

