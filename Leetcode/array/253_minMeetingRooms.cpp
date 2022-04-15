#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// class Solution{
// public:
//     int minMeetingRooms(vector<vector<int>>& intervals){
//         int max_val = -1;
//         for(vector<int>& v:intervals){
//             for(int&  val:v){
//                 max_val =max(max_val,val);
//             }
//         }
//         //直接构建差分数组v
//         vector<int> chafen(max_val+1,0);
//         for(vector<int>& v:intervals){
//             int& i = v[0];
//             int& j = v[1];
//             chafen[i]++;
//             if(j<max_val){
//                 chafen[j+1]--;    
//             }
//         }
//         vector<int> res =hecheng(chafen);
//         int max_res = -1;
//         for(int i=0;i<res.size();i++){
//             max_res = max(max_res,res[i]);
//         }
//         return max_res;

//     }
//     vector<int> hecheng(vector<int>& chafen){
//         vector<int> res(chafen.size());
//         res[0] = chafen[0];
//         for(int i=1;i<res.size();i++){
//             res[i] = res[i-1] + chafen[i];
//         }
//         return res;
//     }
// };

class Solution{
public:
    int minMeetingRooms(vector<vector<int>>& intervals){
        vector<int> start, end;
        for(vector<int>& i:intervals){
            start.push_back(i[0]);
            end.push_back(i[1]);
        }
        sort(start.begin(),start.end());
        sort(end.begin(),end.end());
        int i=0,j=0;
        int res = -1;
        int count =0;
        while(i<start.size()&&j<end.size()){
            if(start[i]<end[j]){
                count++;
                i++;
            }
            else{
                count--;
                j++;
            }
            res = max(res,count);
        }
        return res;
    }
};

int main(){
    
    int M;//组数
    
    cin>>M;
    while(M--){
        Solution s;
        int T;//区间数
        cin>>T;
        vector<vector<int>> intervals;
        while (T--)
        {
            int a,b;
            cin>>a>>b;
            intervals.push_back({a,b});
        }
        cout<<s.minMeetingRooms(intervals);
    }
    return 0;
}