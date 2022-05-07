#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        //找
        int l = 0, r = nums.size()-1;//左闭右闭[l,r]
        while(l<=r){//左闭右闭得结束条件l<=r
            int mid = l + (r-l)/2;
            //升序
            if(nums[mid]<target){
                //当前太小了,
                l = mid+1;
            }
            else if(nums[mid]>target){
                r = mid-1;
            }
            else {
                //相等
                return mid;
            }
        }
        //失败得情况，一直往右招，l越界
        //一直往左找，r越界,l=0

        return l;
    }

};