// #include <vector>
// #include <iostream>
// #include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int i =0, j =0;
        vector<vector<int>> res;
        while(i<firstList.size()&&j<secondList.size()){
            vector<int> f = firstList[i];
            vector<int> s = secondList[j];
            //要的是交集、
            //怎么求交集？
            //不交集：f[0]>s[1] || f[1]<s[0]
            //以上的逆命题就是交集
            if(f[0]<=s[1]&&f[1]>=s[0]){
                int l = max(f[0],s[0]);
                int r = min(f[1],s[1]);
                //也可以直接判断l<=r来判断是否有交集。。
                res.push_back({l,r});
            }
            if(f[1]<s[1]){
                //说明上面该++了;
                i++;
            }
            else {
                j++;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        //已经排好序
        int i=0,j=0;
        vector<vector<int>> res;
        while (i<firstList.size()&&j<secondList.size())
        {
            cout<<i<<" "<<j<<endl;
            vector<int>& f= firstList[i];
            vector<int>& s= secondList[j];

            //要先判断不相交的情况
            if(s[0]<=f[1]&&s[1]>=f[0]){
                //相交
                int start = max(f[0],s[0]);
                int end = min(f[1],s[1]);
                res.push_back({start,end});
            }
            

            if(f[1]<s[1]){
                i++;
            }
            else j++;
        }
        return res;
    }
};