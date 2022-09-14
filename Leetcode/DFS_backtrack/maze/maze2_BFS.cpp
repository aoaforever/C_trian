/*
https://www.nowcoder.com/discuss/1029931?type=all&order=recall&pos=&page=1&ncTraceId=&channel=-1&source_id=search_all_nctrack&gio_id=F8E34CC21AE12D78CE44EAE3C948852C-1663139703475
*/

/*
https://blog.csdn.net/old_Bai/article/details/122670731
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
using namespace std;


vector<vector<int>> visited;
vector<vector<pair<int,int>>> path;
vector<vector<int>> dir{{-1,0},{0,-1},{1,0},{0,1}};
/*::*/
int r,c;

void print(int i, int j){
    //递归，可以顺序打印从入口到出口的路径
    if(i==0&&j==0){
        cout<<"(0,0)"<<endl;
        return ;
    }
    print(path[i][j].first,path[i][j].second);
    cout<<"("<<i<<","<<j<<")"<<endl;
}

void bfs(vector<vector<int>>& maze){
    queue<pair<int,int>> q;
    q.emplace(0,0);
    while(!q.empty()){
        auto [cur_x,cur_y] = q.front();
        q.pop();

        if(cur_x==maze.size()-1&&cur_y==maze[0].size()-1){
            return;
        }

        for(auto d:dir){
            int nx = cur_x+d[0];
            int ny = cur_y +d[1];
            if(nx<0||nx>=maze.size()||ny<0||ny>=maze[0].size()||visited[nx][ny]==1||maze[nx][ny]==1) continue;
            q.emplace(nx,ny);
            path[nx][ny] = make_pair(cur_x,cur_y);
            visited[nx][ny]=1;
        }
    }
}

/*
5 5
0 1 0 0 0
0 1 0 1 0 
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
*/

int main(int argc, char const *argv[])
{
    /* code */
    int r,c;
    cin>>r>>c;

    vector<vector<int>> maze(r,vector<int>(c));
    visited.resize(r,vector<int>(c,0));
    path.resize(r,vector<pair<int,int>>(c));

    ::r = r;
    ::c = c;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>maze[i][j];
        }
    }

    bfs(maze);
    print(maze.size()-1,maze[0].size()-1);
    
    return 0;
}
