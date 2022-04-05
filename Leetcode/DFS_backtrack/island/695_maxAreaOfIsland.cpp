#include<vector>

using namespace std;

//求岛屿最大面积，dfs要返回面积值。
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res=0;
        //剩下的一定是封闭的，直接求面积
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    res= max(res,dfs(grid,i,j));
                }
            }
        }
        return res;

    }
    int dfs(vector<vector<int>>& grid, int x, int y){
        //将岛屿湮灭
        //处理边界问题
        if(x<0||y<0||x>=grid.size()||y>=grid[0].size())
        {
            return 0;
        }

        if(grid[x][y]==0){
            //如果已经是海水，那就返回
            return 0;
        }

        grid[x][y]= 0;
        //继续递归淹没临近的陆地,上下左右

        return 1+dfs(grid,x-1,y)+
        dfs(grid,x+1,y)+
        dfs(grid,x,y-1)+
        dfs(grid,x,y+1);
    }
};