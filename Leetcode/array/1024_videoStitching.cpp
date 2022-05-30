#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        sort(clips.begin(),clips.end(),[](vector<int>&a,vector<int>&b){
            if(a[0]==b[0]){
                return a[1]>b[1];//终点降序
            }
            return a[0]<b[0];//起点升序
        });
        int n = clips.size();
        if(clips[0][0]>0) return -1;
        int res =0;
        int i=0,cur_end=0,next_end=0;
        while(i<n&&clips[i][0]<=cur_end){
            while(i<n&&clips[i][0]<=cur_end){
                next_end = max(clips[i][1],next_end);
                i++;
            }
            res++;
            cur_end=next_end;
            if(cur_end>=time){
                return res;
            }
        }
        return -1;
    }
};

//下面是错误答案
// class Solution {
// public:
//     int videoStitching(vector<vector<int>>& clips, int time) {
//         sort(clips.begin(),clips.end(),[](vector<int>&a, vector<int>&b){
//             if(a[0]==b[0]) return a[1]>b[1];
//             return a[0]<b[0];
//         });
//         int start = clips[0][0];
//         int end = clips[0][1];
//         if(start>0) return -1;
//         int count =1;
//         for(auto& c:clips){
//             int cur_start = c[0];
//             int cur_end = c[1];
//             if(cur_start<=end && cur_end> end){
//                 count++;
//                 start = cur_start;
//                 end = cur_end;
//             }
//         }
//         if(end < time) return -1;
//         return count;
//     }
/*
[[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]]
' +
  '9

  answer = 3
*/
// };
