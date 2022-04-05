#include<vector>

using namespace std;

//求grid2种子岛屿的数目。
//grid2如果是1，但是grid1是0，那么一定不是子岛屿，湮灭
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int res=0;
        //剩下的一定是封闭的，直接求面积
        for(int i=0;i<grid2.size();i++){
            for(int j=0;j<grid2[0].size();j++){
                if(grid2[i][j]==1&&grid1[i][j]==0){
                    dfs(grid2,i,j);
                }
            }
        }
        for(int i=0;i<grid2.size();i++){
            for(int j=0;j<grid2[0].size();j++){
                if(grid2[i][j]==1){
                    dfs(grid2,i,j);
                    res++;
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