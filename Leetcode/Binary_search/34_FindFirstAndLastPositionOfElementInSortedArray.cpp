#include <vector>


//给定一个增序的整数数组和一个值，查找该值第一次和最后一次出现的位置。
//mid是要找的数了，下一次怎么确定该往左边还是右边走呢？

//这道题可以看作是自己实现C++ 里的lower_bound 和upper_bound 函数。这里我们尝试使用左闭右开的写法，当然左闭右闭也可以。
using namespace std;

//这个版本超时了？？
class Solution{
public:
    //一直往左找，就是最左边的位置
    int lower_bound(vector<int>&nums, int target){//数组和要找的数
        int left=0, right=nums.size(), mid;
        while(left<right){
            mid = left + (right-left)/2;

            if(nums[mid]==target){
                right=mid;
            }
            else if(nums[mid]<target){
                left=mid+1;
            }
            else {
                right=mid-1;
            }
        }
        return left;//应该是return left， 应为如果是目标数，right=mid-1;left还是=mid;
    }

    int upper_bound(vector<int>&nums, int target){
        int left=0, right=nums.size(), mid;
        while(left<right){//不能相等
            mid=left+ (right-left)/2;

            if(nums[mid]==target){
                left = mid;//不能-1
            }
            else if (nums[mid]<target){
                left=mid+1;
            }
            else {
                right=mid-1;
            }

        }
        return left;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return vector<int>{-1,-1};

        int lower = lower_bound(nums,target);
        int upper = upper_bound(nums,target);

        if(nums[lower]!=target || lower==nums.size()){
            return vector<int>{-1,-1};
        }

        return vector<int>{lower,upper};

    }

};

#include <vector>


//这个版本可以
class Solution{
public:
    //一直往左找，就是最左边的位置
    int lower_bound(vector<int>&nums, int target){//数组和要找的数
        int left=0, right=nums.size(), mid;
        while(left<right){
            mid = left + (right-left)/2;

            if(nums[mid]>=target){
                right=mid;
            }
            else if(nums[mid]<target){
                left=mid+1;
            }
        }
        return left;//应该是return left， 应为如果是目标数，right=mid-1;left还是=mid;
    }

    int upper_bound(vector<int>&nums, int target){
        int left=0, right=nums.size(), mid;
        while(left<right){//不能相等
            mid=left+ (right-left)/2;

            if(nums[mid]<=target){
                left = mid+1;//不能-1，因为左闭右开，所以左可以加1
            }
            else {
                right=mid;
            }

        }
        return left;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return vector<int>{-1,-1};

        if(nums.size()==1 && nums[0]==target) return vector<int>{0,0};

        int lower = lower_bound(nums,target);
        int upper = upper_bound(nums,target)-1;//为什么减一，因为左闭右开，右一开始是指向越界的。

        if(  lower==nums.size()||nums[lower]!=target){//顺序不能反。
            return vector<int>{-1,-1};
        }

        return vector<int>{lower,upper};

    }

};

/*
考虑4种情况
1. 目标不在数组内，并且在数组左边，rigth会一直mid-1,直到不满足left<=right,此时right在left的左边，right在数组的左边,nums[left]!=target
2. 目标不在数组内，并且在数组右边，left会一直mid+1，直到不满足left<=right,此时left在right的右边，left在数组的右边,left=nums.size()
3. 目标在数组内，但是数组没有这个元素，left和right会一直更新，直到不满足left<=right,此时left在right的右边，left在数组内，nums[left]!=target
4. 目标在数组内，数组有这个元素。
4.1 左边界，最终left会在target的最左边，包含target
4.2 右边界，最终left会在target的最右边，不包含target，而right正是target的最 
0.
右边
*/

class Solution{
public:
    int lower_bound(vector<int>&nums, int target){//找左边界，就是右一直往左靠
        int left=0, right=nums.size()-1, mid;//左闭右闭
        while(left<=right){
            mid=left+ (right-left)/2;

            if(nums[mid]<target)
                left=mid+1;
            else    
                right = mid-1;

        }
        return left;//包含target的最左边
    }

    int upper_bound(vector<int>&nums, int target){//找右边界，就是左一直往右靠
        int left =0, right=nums.size()-1, mid;//左闭右闭
        while(left<=right){
            mid = left + (right-left)/2;

            if(nums[mid]<=target)
                left = mid+1;
            else 
                right = mid-1;

        }
        return left-1;//包含target的最右边
    }
    vector<int> searchRange(vector<int>& nums, int target){
        if(nums.empty()) return vector<int>{-1,-1};

        int lower = lower_bound(nums,target);
        int upper = upper_bound(nums,target);

        //判断不存在target的情况
        if(lower==nums.size()||nums[lower]!=target)
            return vector<int>{-1,-1};

        return vector<int>{lower,upper};
    }
};







//二刷答案
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        //已经升序排列，找出左右边界
        int l = left_bound(nums,target);
        int r = right_bound(nums,target);
        return {l,r};
    }
    int left_bound(vector<int>&nums,int target){
        //找左边界
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
                //相等，但是找左区间，因此
                r = mid-1;
            }
        }
        //失败得情况，一直往右招，l越界
        //一直往左找，r越界,l=0
        if(l>=nums.size()||nums[l]!=target){
            return -1;
        }
        return l;
    }
    int right_bound(vector<int>&nums,int target){
        //找右边界
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
                //相等，但是找右区间，因此
                l = mid+1;
            }
        }
        //失败得情况，一直往右招，l越界
        //一直往左找，r越界,l=0
        if(r<0||nums[r]!=target){
            return -1;
        }
        return r;//找最简单得例子[7,7]就可以得出
    }
};