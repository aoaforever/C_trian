#include<vector>

using namespace std;

//飞地其实是封闭的 陆地面积。
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int res=0;
        //先把边缘的地给淹没掉。
        for(int i=0;i<grid.size();i++){
            dfs(grid,i,0);
            dfs(grid,i,grid[0].size()-1);
        }
        for(int i=0;i<grid[0].size();i++){//注意是列。
            dfs(grid,0,i);
            dfs(grid,grid.size()-1,i);
        }
        //剩下的一定是封闭的，直接求面积
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    res++;
                }
            }
        }
        return res;

    }
    void dfs(vector<vector<int>>& grid, int x, int y){
        //将岛屿湮灭
        //处理边界问题
        if(x<0||y<0||x>=grid.size()||y>=grid[0].size())
        {
            return ;
        }

        if(grid[x][y]==0){
            //如果已经是海水，那就返回
            return;
        }

        grid[x][y]= 0;
        //继续递归淹没临近的陆地,上下左右
        dfs(grid,x-1,y);
        dfs(grid,x+1,y);
        dfs(grid,x,y-1);
        dfs(grid,x,y+1);

    }
};