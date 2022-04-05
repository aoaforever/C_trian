#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <set>
using namespace std;
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

int main(){
    vector<vector<int>> board{
        {2,1,3},
        {4,5,0}
    };
    Solution a;
    a.slidingPuzzle(board);
    return 0;
}