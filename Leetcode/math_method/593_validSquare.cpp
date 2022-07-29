/*
593. 有效的正方形
给定2D空间中四个点的坐标 p1, p2, p3 和 p4，如果这四个点构成一个正方形，则返回 true 。

点的坐标 pi 表示为 [xi, yi] 。输入 不是 按任何顺序给出的。

一个 有效的正方形 有四条等边和四个等角(90度角)。

 

示例 1:

输入: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
输出: True
示例 2:

输入：p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
输出：false
示例 3:

输入：p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
输出：true
 

提示:

p1.length == p2.length == p3.length == p4.length == 2
-104 <= xi, yi <= 104
*/
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        set<int> p;

        p.emplace(len(p1,p4));
        p.emplace(len(p1,p3));
        p.emplace(len(p2,p4));
        p.emplace(len(p2,p3));
        p.emplace(len(p1,p2));//对角线
        p.emplace(len(p3,p4));//对角线
        // cout<<p[0]<<" "<<p[1]<<" "<<p[0]<<" "<<p[2]<<" "<<p[0]<<" "<<p[3]<<" "<<p[4]<<" "<<p[5]<<endl;
        if(p.size()!=2||p.count(0)) return false;
        
        vector<int> a;
        for(auto i:p){
            a.push_back(i);
        }
        if(a[0]*2==a[1]) return true;
        return false;
    }
    int len(vector<int>& a, vector<int>& b){
        int & x0 = a[0] , &x1 = b[0];
        int & y0 = a[1] , &y1 = b[1];
        //[x0,y0], [x1,y1]

        return (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1);//其实返回的是长度的平方
    }
};