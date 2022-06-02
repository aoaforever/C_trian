/*
 * @lc app=leetcode.cn id=1584 lang=cpp
 *
 * [1584] 连接所有点的最小费用
 *
 * https://leetcode-cn.com/problems/min-cost-to-connect-all-points/description/
 *
 * algorithms
 * Medium (66.14%)
 * Likes:    209
 * Dislikes: 0
 * Total Accepted:    36.1K
 * Total Submissions: 54.6K
 * Testcase Example:  '[[0,0],[2,2],[3,10],[5,2],[7,0]]'
 *
 * 给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。
 * 
 * 连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示
 * val 的绝对值。
 * 
 * 请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
 * 输出：20
 * 解释：
 * 
 * 我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
 * 注意到任意两个点之间只有唯一一条路径互相到达。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：points = [[3,12],[-2,5],[-4,1]]
 * 输出：18
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：points = [[0,0],[1,1],[1,0],[-1,1]]
 * 输出：4
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：points = [[-1000000,-1000000],[1000000,1000000]]
 * 输出：4000000
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：points = [[0,0]]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= points.length <= 1000
 * -10^6 <= xi, yi <= 10^6
 * 所有点 (xi, yi) 两两不同。
 * 
 * 
 */

// @lc code=start
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        vector<vector<int>> edges;
        for(int i=0;i<points.size();i++){
            for(int j=i+1;j<points.size();j++){
                int xi = points[i][0], yi = points[i][1];
                int xj = points[j][0], yj = points[j][1];
                edges.push_back(
                    {i,j,
                    abs(xi-xj)+abs(yi-yj)
                    }
                );//给每个坐标用一维来表示
            }
        }
        if(edges.size()==0) return 0;

        sort(edges.begin(),edges.end(),[](vector<int>&a, vector<int>&b){
            return a[2]<b[2];
        });
        //uf的节点从来都不是边数组的长度，而是节点总数。而points的size就是点的个数，edges.size才是边的个数
        UF uf(points.size());//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int res=0;
        for(auto& e:edges){//而遍历是遍历每一条边，而不是每个节点。
            int i = e[0];
            int j=  e[1];
            int val = e[2];

            if(uf.connected(i,j)) continue;
            uf.union_(i,j);
            res+= val;
        }
        return res;
    }

    class UF{
private:
    vector<int> parent;//每个节点的父节点
    int count;//通量
    vector<long> size;//每个节点为根的size// 居然会有溢出的情况，所以用long
public:
    UF(int n){
        //n个节点
        parent.resize(n);
        size.resize(n);//你忘了这个
        for(int i=0;i<n;i++){
            parent[i] =i;//先每个节点都指向自己。
            size[i] =1;//每个节点的size都为1.
        }
        count = n;

    }
    bool connected(int a,int b){
        int roota = find(a);
        int rootb = find(b);
        if(roota==rootb) return true;
        return false;
    };
    void union_(int a,int b){
        int roota= find(a);
        int rootb = find(b);
        if(size[roota]>=size[rootb]){
            //那就挂在roota下
            parent[rootb] = roota;
            count--;
            size[roota] += size[rootb];
        }else{
            parent[roota] = rootb;
            count--;
            size[rootb] += size[roota];
        }
    };
    int find(int a){
        while(a!=parent[a]){
            parent[a] = parent[parent[a]];
            a= parent[a];
        }
        return a;
    };
    int get_count(){
        return count;
    }
};
};
// @lc code=end

