#include <vector>
using namespace std;

//1表示陆地，0是水,而且注意是个字符卧槽

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0||grid[0].size()==0 ) return 0;
        int res =0;//要初始化为0，不然不确定答案
        int row = grid.size();
        int col = grid[0].size();
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j] == '1' ){
                    //如果是陆地，数量加1，然后淹没
                    res++;
                    dfs(grid,i,j);
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<char>>& grid, int x, int y){
        //将岛屿湮灭
        //处理边界问题
        if(x<0||y<0||x>=grid.size()||y>=grid[0].size())
        {
            return ;
        }

        if(grid[x][y]=='0'){
            //如果已经是海水，那就返回
            return;
        }

        grid[x][y]= '0';
        //继续递归淹没临近的陆地,上下左右
        dfs(grid,x-1,y);
        dfs(grid,x+1,y);
        dfs(grid,x,y-1);
        dfs(grid,x,y+1);

    }
};