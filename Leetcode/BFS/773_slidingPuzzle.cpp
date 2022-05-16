#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <set>
using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target ="123450";
        string sb="";
        for(auto& b:board){
            for(auto& i:b){
                sb+=to_string(i);
            }
        }
        cout<<sb<<endl;
        vector<vector<int>> dir{
            {1,3},
            {0,2,4},
            {1,5},
            {0,4},
            {1,3,5},
            {2,4}
        };
        set<string> used;
        queue<string> q;
        q.push(sb);
        used.insert(sb);
        int step=0;
        while(!q.empty()){
            int sz=q.size();
            for(int i=0;i<sz;i++){
                string tmp = q.front();
                q.pop();
                int index = tmp.find('0');
                cout<<index<<endl;
                if(tmp==target) return step;     
                for(int& d:dir[index]){
                    //和dd位置交换
                    string t = tmp;
                    swap(t[index],t[d]);
                    if(used.count(t)){
                        continue;
                    }
                    used.insert(t);
                    q.push(t);
                    
                }
            }
            step++;
        }
        return -1;

    }
};

//首先将二维打成3维。 本来是固定2x3，打成一维，可以快速找到映射
//如果找不到：if(!used.count(tmp))  或 if(used.find(tmp)==used.end())


class Solution {
public:
    vector<vector<int>> neiborhor{
        {1,3},//0的近邻
        {0,2,4},//1的近邻
        {1,5},
        {0,4},
        {1,3,5},
        {2,4}
    };

    int slidingPuzzle(vector<vector<int>>& board) {
        //将2x3打平成1x6的字符串
        string start = "";
        string target="123450";     
        set<string> used;
        for(int i=0;i<2;i++){
            for(int j=0;j<3;j++){
                start += to_string(board[i][j]);
            }
        }
        int step = 0;
        cout<<start;
        queue<string> q;
        q.push(start);
        used.insert(start);
        
        while (!q.empty())
        {
            int sz = q.size();
            for(int k=0;k<sz;k++){
                string cur = q.front();
                q.pop();
                if(cur == target){
                    return step;
                }
                
                //没理由加下面这句啊。。。。
                // if(used.find(cur)!=used.end()) continue;

                int index = -1;
                //先找到0的位置
                for(int i=0;i<cur.size();i++){
                    if(cur[i]=='0'){
                        index=i;
                    }
                }
                //将0和附近的位置交换获得新的节点
                //二话不说，先把子节点添加上
                vector<int> n = neiborhor[index];
                for(int j=0;j<n.size();j++){
                    string tmp = cur;
                    swap(tmp[index],tmp[n[j]]);
                    if(used.find(tmp)==used.end()){
                        q.push(tmp);
                        used.insert(tmp);
                    }
                    
                }
                
            }
            step++;
        }
        return -1;
    }
};

//超时做法
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        vector<vector<int>> target{{1,2,3},{4,5,0}};
        int r=2,c=3;
        queue<vector<vector<int>>> q;
        q.push(board); 
        int step=0;
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;i++){
                vector<vector<int>> tmp=q.front();
                q.pop();
                if(tmp==target) return step;
                //对tmp的移动情况列举
                //找出0的位置，向上下左右移动
                int r,c;
                find(board,r,c);
                if(left(board,r,c)){
                    vector<vector<int>> l(tmp);
                    swap(l[r][c],l[r][c-1]);
                    q.push(l);
                };
                if(up(board,r,c)){
                    vector<vector<int>> u(tmp);
                    swap(u[r][c],u[r-1][c]);
                    q.push(u);
                };
                if(down(board,r,c)){
                    vector<vector<int>> d(tmp);
                    swap(d[r][c],d[r+1][c]);
                    q.push(d);
                };
                if(right(board,r,c)){
                    vector<vector<int>> ri(tmp);
                    swap(ri[r][c],ri[r][c+1]);
                    q.push(ri);
                };
            }
            step++;
        }
        return -1;
    }
    bool left(vector<vector<int>>&board,int i,int j){
        if(j-1<0) return false;
        return true;
    }
    bool up(vector<vector<int>>&board,int i,int j){
        if(i-1<0) return false;
        return true;
    }
    bool down(vector<vector<int>>&board,int i,int j){
        if(i+1>1) return false;
        return true;
    }
    bool right(vector<vector<int>>&board,int i,int j){
        if(j+1>2) return false;
        return true;
    }    
    void find(vector<vector<int>>& board,int &i,int &j){
        for(int r=0;r<2;r++){
            for(int c=0;c<3;c++){
                if(board[r][c]==0){
                    i=r;
                    j=c;
                }
            }
        }
    }

};


int main(){
    vector<vector<int>> board{
        {2,1,3},
        {4,5,0}
    };
    Solution a;
    a.slidingPuzzle(board);
    return 0;
}