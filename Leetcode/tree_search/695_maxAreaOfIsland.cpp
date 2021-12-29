#include<vector>
#include <algorithm>

using namespace std;
/*这个会把原来的grid遍历过后都给置0*/
class Solution{
public:

    vector<int> direction{-1,0,1,0,-1};

    int maxAreaOfIsland(vector< vector<int> >& grid){
        if(grid.empty() || grid[0].empty()) return 0;

        int max_area=0;
        for(int i=0;i<grid.size();++i){//只是行数
            for(int j =0; j<grid[0].size();++j){//列数
                if(grid[i][j]==1){
                    max_area = max(max_area,dfs(grid,i,j));
                }

            }

        }
    }

    int dfs(vector< vector<int> >& grid, int r , int c){
        //这是递归
        /*边界判定一般
有两种写法，一种是先判定是否越界，只有在合法的情况下才进行下一步搜索（即判断放在调用
递归函数前）；*/
        if (grid[r][c]==0) return 0;

        grid[r][c]=0;//先把当前置零
        int x , y , area =1;
        for(int i=0; i<4; ++i){//找4个方向
            x = r+ direction[i];
            y = c + direction[i+1];//上右下左分别进行

            if(x>=0 && x<grid.size() && y>=0 && y<grid[0].size()){
                area += dfs(grid,x,y);
            }
        }
        return area;
    }
};