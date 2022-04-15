#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//还可以继续优化逻辑，不过没关系了。。

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
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
        int l = intervals[0][0];
        int r =intervals[0][1];
        res.push_back({l,r});
        for(int i=1;i<intervals.size();i++){
            int cur_l = intervals[i][0];
            int cur_r = intervals[i][1];

            if(cur_l<=r){
                //相交，或者包括需要合并
                r = max(r,cur_r);
                res.back()[1] = r;
            }

            if(r<cur_r){
                //不相交，更新结果
                res.push_back({cur_l,cur_r});
                l=cur_l;
                r=cur_r;
            }
        }       

        return res;
    }
};