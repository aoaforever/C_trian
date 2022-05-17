#include <iostream>
#include<vector>
#include <string>
#include <set>
#include <map>
using namespace std;

//⼒扣第 694 题「不同的岛屿数量」，题⽬还是输⼊⼀个⼆维矩阵，0 表示海⽔，1 表示陆地，这次让你计算
// 不同的 (distinct) 岛屿数量，函数签名如下：P383

//不同可以用遍历顺序序列化来辨别。用一个set唯一存，如果有重复，则不计入

// class Solution {
// public:
//     int numDistinctIslands(vector<vector<int>>& grid) {
        
//         set<string> res;
//         //剩下的一定是封闭的，直接求面积
//         for(int i=0;i<grid.size();i++){
//             for(int j=0;j<grid[0].size();j++){
//                 if(grid[i][j]==1){
//                     string ss;
//                     dfs(grid,i,j,ss,666);
//                     // cout<<ss<<endl;
//                     res.insert(ss);
//                 }
//             }
//         }
//         return res.size();

//     }
//     void dfs(vector<vector<int>>& grid, int x, int y,string& s,int dir){
//         //将岛屿湮灭
//         //处理边界问题
//         if(x<0||y<0||x>=grid.size()||y>=grid[0].size())
//         {
//             return ;
//         }

//         if(grid[x][y]==0){
//             //如果已经是海水，那就返回
//             return ;
//         }

//         grid[x][y]= 0;
//         //继续递归淹没临近的陆地,上下左右
//         //不仅要记录前向，还要记录撤销向
//         s += to_string(dir) + "," ;
//         dfs(grid,x-1,y,s,1);
//         dfs(grid,x+1,y,s,2);
//         dfs(grid,x,y-1,s,3);
//         dfs(grid,x,y+1,s,4);
//         s += to_string(-dir)+",";

        
//     }
// };

// int main(){
//     vector<vector<int>> grid{{1,1,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};
//     Solution s;
//     cout<<s.numDistinctIslands(grid)<<endl;
//     // string sasd;
//     // sasd += to_string(123);
//     // cout<<sasd<<endl;
//     return 0;

// }


class Solution {
public:
    int r,c;
    int numDistinctIslands(vector<vector<int>>& grid) {
        r=grid.size();
        c = grid[0].size();
        set<string> d;
        int res=0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(grid[i][j]==1){
                    string s="";
                    dfs(grid,i,j,s,666);
                    cout<<s<<endl;
                    if(!d.count(s))  {
                        res++;
                        d.insert(s);
                    }
                    
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<int>>& grid,int i,int j, string& s,int d){
        //将岛屿湮灭
        //处理边界问题
        if(i<0||j<0||i>=r||j>=c||grid[i][j]==0){
            
            return;
        }

        
        grid[i][j] = 0;
        s += to_string(d)+",";
        dfs(grid,i-1,j,s,1);//上
        dfs(grid,i+1,j,s,2);//下
        dfs(grid,i,j-1,s,3);//左
        dfs(grid,i,j+1,s,4);//右
        s += to_string(-d)+",";
    }
};

int main(){
    vector<vector<int>> grid{{1,1,0,1,1},{1,0,0,0,0},{0,0,0,0,1},{1,1,0,1,1}};
    Solution s;
    cout<<s.numDistinctIslands(grid)<<endl;
    // string sasd;
    // sasd += to_string(123);
    // cout<<sasd<<endl;
    return 0;

}