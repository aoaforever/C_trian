#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void insertion_sort(vector<int>&nums, int n ){
    for(int i =0; i <n ;++i){
        for(int j = i; j>0 && nums[j]<nums[j-1] ; --j){
            swap(nums[j],nums[j-1]);
        }
    }
}

int main(){
    vector<int> a{1,2,3,9,8,7,6,5,4,3};
    insertion_sort(a,a.size());
    for(int i:a){
        cout<<i<<" ";
    }
    return 0;
} 

