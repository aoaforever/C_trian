#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//会超时
class Solution {
public:
    int maxArea(vector<int>& height) {
        //暴力法
        int res=INT_MIN;
        for(int i=0;i<height.size();i++){
            for(int j=i;j<height.size();j++){
                int area = (j-i)*min(height[i],height[j]);
                res = max(res,area);
            }
        }
        return res;
    }
};
//优化的思路在于：暴力是无脑的移动指针，而头尾指针根据只移动较低的指针，从而达到下一次可能会增大的情况，来移动指针
//如果移动较高的指针，那么下次的面积取决于未移动的低指针。
//双指针，从两端进行
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res=INT_MIN;
        int i=0,j=height.size()-1;//左闭右闭[i,j]
        while(i<j){
            int area = (j-i)*min(height[i],height[j]);
            res = max(res,area);
            if(height[i]<height[j]){
                //左边矮
                i++;
            }
            else{
                j--;
            }
        }
        return res;
    }
};