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