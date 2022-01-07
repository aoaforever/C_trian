#include <vector>
#include <queue>
#include <iostream>
using namespace std;


/*在给定的二维二进制数组 A 中，存在两座岛。（岛是由四面相连的 1 形成的一个最大组。）

现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一座岛。

返回必须翻转的 0 的最小数目。（可以保证答案至少是 1 。）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shortest-bridge
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
class Solution{
public:
    vector<int> direction{-1,0,1,0,-1};
    int shortestBridge(vector<vector<int>>& grid){
        int m=grid.size(), n = grid[0].size();
        queue<pair<int,int>> points;//points表示海
        //dfs寻找第一个岛屿，并把1全部赋值为2.

        bool flipped =false;
        //points:3,3    3,2    3,1    3,1    2,1    1,1    3,3    2,3    1,3    1,3    1,2    1,1    
        //会有很多从重复的元素。
        for(int i=0;i<m;i++){
            if(flipped) break;
            for(int j = 0 ; j<n;j++){
                if(grid[i][j]==1){
                    dfs(points,grid,m,n,i,j);
                    flipped=true;
                    break;
                }
            }
        }

        //bfs寻找第二个岛屿，并把过程中经过的0赋值为2.
        //是bfs！！
        //因为是按层搜索，都会先迈出第一步，当第二步已经到达了，就不需要第三步了。
        int x,y;
        int level = 0 ; 
        while(!points.empty()){
            ++level;
            int n_points=points.size();
            while(n_points--){
                auto [r,c] = points.front();
                points.pop();
            // int s = points.size();
        //     while(s--){
        //     pair<int,int> tmp = points.front();
        //     points.pop();
        //     cout<<tmp.first<<","<<tmp.second<<"    ";
        //     points.push(tmp);
        // }
        // cout<<endl;
                for(int k=0; k<4; k++){
                    x= r+direction[k];
                    y= c+direction[k+1];

                    if(x>=0&&x<m&&y>=0&&y<n){
                        if(grid[x][y]==2){
                            continue;//走到了第一个岛屿
                        }
                        if(grid[x][y]==1){
                            return level;
                        }
                        // printf("[%d,%d]",x,y);
                        points.push({x,y});
                        grid[x][y]=2;
                    }
                }
            }

        }
        return 0;
    }
    
    void dfs(queue<pair<int,int>>&points, vector<vector<int>>&grid, int m, int n, int i, int j){
        //不管三七二十一，先递归再说。
        if(i<0||i>=m||j<0||j>=n||grid[i][j]==2){
            return;
        }

        if(grid[i][j]==0){
            points.push({i,j});//把海都记录下来
            return ;
        }

        grid[i][j]=2;//把遍历过的点置为2
        dfs(points,grid,m,n,i,j+1);
        dfs(points,grid,m,n,i+1,j);
        dfs(points,grid,m,n,i-1,j);
        dfs(points,grid,m,n,i,j-1);

    }

};

int main(){
    Solution solution;
    vector<vector<int>> a{{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    solution.shortestBridge(a);

    //3,3    3,2    3,1    3,1    2,1    1,1    3,3    2,3    1,3    1,3    1,2    1,1    

    //3,2    3,1    3,1    2,1    1,1    3,3    2,3    1,3    1,3    1,2    1,1    2,3    3,2    
    //3,3退出队列，加入了2,3和3,2两个元素。
    return 0;
}