#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//在vscode不会检查nums越界，但是leetcode会，因此partition中如果一开始Lo==hi,就应该直接结束。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //第一个最大的元素对应排序后的size-1下标
        //第k最大的元素对应排序后的size-k下标。
        int lo = 0, hi = nums.size()-1;//左闭右闭
        int n_k = nums.size()-k;
        while(lo<=hi){
            int p = partition(nums,lo,hi);
            if(p<n_k){
                //需要往右找
                lo = p+1;
            }
            else if(p>n_k){
                //需要往左找
                hi = p-1;
            }
            else {
                return nums[p];
            }
        }
        return -1;
    }
    int partition(vector<int>&nums,int lo,int hi){
        int pivot = nums[lo];
        int i=lo,j=hi+1;
        while(true){
            //先对i做操作
            while(nums[++i]<pivot){
                if(i>=hi) break;
            }
            while(nums[--j]>pivot){//右边要大于才能一直减
                if(j<=lo) break;
            }
            if(i>=j) break;
            swap(nums[i],nums[j]);

        }
        //跳出后，j位置的元素是<pivot的，而目前pivot在lo位置，所以交换。
        //nums[i]>pivot，所以才停下来。
        //nums[j]<pivot，所以才停下来。
        swap(nums[lo],nums[j]);
        cout<<j<<" ";
        return j;
    }
};

int main(){
    Solution s;
    vector<int> nums={1};
    s.findKthLargest(nums,1);
    return 0;
}