#include<vector>
using namespace std;

class Solution{
public:
    int findCircleNum(vector<vector<int>>& friends){
        int n = friends.size() , count = 0 ;
        vector<bool> visited(n,false);

        for(int i =0; i< n; i++){
            if(!visited[i]){//如果还没有访问过它
                dfs(friends,i , visited);//如果全部相连，则会在这里一次性访问到，朋友圈个数为1
                ++count;
            }
        }
        return count;
    }

    void dfs(vector<vector<int>>&friends, int i , vector<bool>& visited){
        if (visited[i]) return;
        visited[i]=true;
        //i这为朋友和0~n-1朋友的关系
        for(int j =0;j<friends[0].size();j++){
            if(friends[i][j]==1 && !visited[j]){ //!visited[j]是自己没有想到的。
                dfs(friends,i+1,visited);
            }
        }
    }

};