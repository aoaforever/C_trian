#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        memo = vector<vector<int>>(dungeon.size(),vector<int>(dungeon[0].size(),-1));
        return dp(dungeon,0,0);
    }

    //dp代表i，j得最少初始生命值
    int dp(vector<vector<int>>&dungeon,int i,int j){
        //base case
        //越界
        if(i>=dungeon.size()||j>=dungeon[0].size()){return INT_MAX;}
        //结束条件
        if(i==dungeon.size()-1 && j==dungeon[0].size()-1){
            //如果当前是负值，因为初始生命值必须>=1, 因此如果要经过这个位置，那么初始生命值就是-dungeon[i][j]+1，
            // 这样经过这个位置之后的生命值就剩1。
            //如果当前位置是正值，那就无所谓，取个最小初始值1.
            return dungeon[i][j]<=0? -dungeon[i][j]+1 : 1; //这里会出错。
        }
        if(memo[i][j]!=-1) return memo[i][j];
        int res;
        //从右和下决定当前的最低初始健康点数
        int right = dp(dungeon,i,j+1);
        int down = dp(dungeon,i+1,j);
        res = min(right,down) - dungeon[i][j] ;
        
        res = res<=0?1:res;
        memo[i][j] = res;
        return memo[i][j];
    }
};