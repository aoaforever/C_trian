/*
https://www.nowcoder.com/discuss/1029931?type=all&order=recall&pos=&page=1&ncTraceId=&channel=-1&source_id=search_all_nctrack&gio_id=F8E34CC21AE12D78CE44EAE3C948852C-1663139703475
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> res;
vector<vector<int>> ans;
vector<vector<int>> visited;
vector<vector<int>> dir{{-1,0},{0,-1},{1,0},{0,1}};
/*::*/
int r,c;

bool backtrack(vector<vector<int>>& maze,int i,int j,vector<vector<int>>& res){
    //从左上角走到右下角
    if(i==maze.size()-1&&j==maze[0].size()-1){
        
        ans = res;
        return true;
    }
    
    
    for(auto d:dir){
        int ni = i+d[0];
        int nj = j+d[1];
        if(ni<0||ni>=r||nj<0||nj>=c||visited[ni][nj]==1||maze[ni][nj]==1) continue;
        visited[ni][nj]=1;
        res.push_back({ni,nj});
        if(backtrack(maze,ni,nj,res)) return true;
        visited[ni][nj] = 0;
        res.pop_back();
    }
    

}

int main(int argc, char const *argv[])
{
    /* code */
    int r,c;
    cin>>r>>c;

    vector<vector<int>> maze(r,vector<int>(c));
    visited.resize(r,vector<int>(c,0));
    ::r = r;
    ::c = c;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>maze[i][j];
        }
    }

    res.push_back({0,0});
    backtrack(maze,0,0,res);
    for(int i=0;i<res.size();i++){
        cout<<"("<<res[i][0]<<","<<res[i][1]<<")"<<endl;
    }
    return 0;
}
