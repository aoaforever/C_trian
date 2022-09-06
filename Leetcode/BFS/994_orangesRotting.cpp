#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;
class Solution {
public:

    int count;
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        count=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                string t;
                t += to_string(i)+","+to_string(j);
                
                if(grid[i][j]==1) count++;
                if(grid[i][j]==2) q.emplace(i,j);
            }
        }

        int ans=0;

        while(!q.empty()){
            int sz = q.size();
            for(int k=0;k<sz;k++){
                auto [i,j] = q.front();
                q.pop();
                //pop出来的一定是腐烂的，则扩散四周
                vector<pair<int,int>> res = milan(grid,i,j);
                if(res.empty()) continue;
                for(pair<int,int>& r:res){
                    q.emplace(r.first,r.second);
                }
            }
            if(!q.empty()){
                ans++;
            }
            
        }
        // cout<<count<<endl;
        if(count!=0) return -1;
        return ans;

    }

    vector<pair<int,int>> milan(vector<vector<int>> & grid, int i , int j){
        //上i-1,j
        //下i+1,j
        //左i,j-1
        //右i,j+1
        vector<pair<int,int>> res;
        if(i-1>=0){
            if(grid[i-1][j]==1){
                grid[i-1][j]=2;
                count--;
                res.emplace_back(i-1,j);
            }
        }
        if(i+1<grid.size()){
            if(grid[i+1][j]==1){
                grid[i+1][j]=2;
                count--;


                res.emplace_back(i+1,j);
            }
        }
        if(j+1<grid[0].size()){
            if(grid[i][j+1]==1){
                grid[i][j+1]=2;
                count--;

                res.emplace_back(i,j+1);
            }
        }
        if(j-1>=0){
            if(grid[i][j-1]==1){
                grid[i][j-1]=2;
                count--;

                res.emplace_back(i,j-1);
            }
        }
        return res;
    }
};