#include <vector>
#include <iostream>
using namespace std;

/*

1. 先对第一个元素进行快速排序，放到中间后判断mid==target？
2. 如果mid<target，说明要往右边排序，可以丢弃左边的
3. 如果mid>target，说明要往左边排序，可以丢弃右边的
*/
// class Solution{
// public:
//     //辅助函数-快速选择
//     int quickSelection(vector<int>& nums, int l , int r){
//         int i=l+1, j=r;
//         while(true){
//             while(i<r&& nums[i]<= nums[l]){
//                 ++i;
//             }
//             while(l<j&&nums[j]>=nums[l]){
//                 --j;
//             }

//             if(i>=j){
//                 break;
//             }

//             swap(nums[i],nums[j]);
//         }
//         swap(nums[l],nums[j]);
//         return j ;
//     }

//     int findKthLargest(vector<int>& nums, int k ){
//         int l=0, r=nums.size()-1, target = nums.size()-k;
        
//         while(l<r){
//             int mid = quickSelection(nums,l,r);//返回的j刚好是mid下标。

//             if(mid==target){
//                 return nums[mid];
//             }
//             if(mid<target){
//                 l = mid+1;
//             }
//             else {
//                 r= mid-1;
//             }
//         }
//         return nums[l];
//     }

// };


class Solution{
public:
    //辅助函数-快速选择
    int quickSelection(vector<int>& nums, int l , int r){
        int i=l, j=r,key = nums[l];
        while(i<j){
            while(i<j&&nums[j]>= key ){
                --j;
            }
            nums[i]=nums[j];
            while(i<j&& nums[i]<= key){
                ++i;
            }
            nums[j]=nums[i];
            // swap(nums[i],nums[j]);
        }
        // nums[l]=nums[i];
        nums[i]=key;
        // swap(nums[l],nums[j]);
        return i ;
    }

    int findKthLargest(vector<int>& nums, int k ){
        int l=0, r=nums.size()-1, target = nums.size()-k;
        
        while(l<r){
            int mid = quickSelection(nums,l,r);//返回的j刚好是mid下标。
            cout<<mid<<endl;
            if(mid==target){
                return nums[mid];
            }
            if(mid<target){
                l = mid+1;
            }
            else {
                r= mid-1;
            }
        }
        return nums[l];
    }

};

int main(){ 
    vector<int> a{3,2,1,5,6,4};
    Solution solution;
    solution.findKthLargest(a,2);
    return 0;
}