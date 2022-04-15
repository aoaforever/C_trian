#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        //对intervals排序
        sort(intervals.begin(),intervals.end(),[](vector<int>&a,vector<int>&b){
            //如果开始相同，则按后面排
            if(a[0]==b[0]){
                return a[1]>b[1];//尾部降序
                //为什么尾部降序？
                //因为是从左到右遍历的，这样降序的下一个如果被包含就能够监测的到。
            }
            //默认是升序
            return a[0]<b[0];
        });
        int left = intervals[0][0];
        int right = intervals[0][1];
        int res=0;
        for(int i=1;i<intervals.size();i++){
            int cur_l = intervals[i][0];
            int cur_r = intervals[i][1];
            if(left<=cur_l&&right>=cur_r){
                //被包含
                res++;
            }
            if(cur_l<=right&&cur_r>right){
                //相交
                right = cur_r;
            }
            if(cur_l>right){
                //没有任何相交
                left = cur_l;
                right = cur_r;
            }
        }
        //返回的是剩余数目啊！！！！
        return intervals.size()-res;
    }
};