#include <vector>

using namespace std;

int binarySearch(vector<int> nums, int target){
    int left=0, right=...;

    while(...){
        int mid = left+(right-left)/2;
        if(nums[mid]==target){
            ...
        }
        else if(nums[mid]<target){
            left = ...;
        }
        else{
            right = ...;
        }
    }
    return ...;
}