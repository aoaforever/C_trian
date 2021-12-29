#include <vector>
#include <iostream>

using namespace std;

void selection_sort(vector<int> &nums, int n ){
    int mid;
    for(int i =0; i<n-1;i++){
        mid=i;//记录最小值下标
        for(int j=i+1;j<n;j++){
            if(nums[j]<nums[mid]){
                mid=j;
            }
        }
        swap(nums[i],nums[mid]);
    }
}

int main(){
    vector<int> a{1,2,3,9,8,7,6,5,4,3};
    selection_sort(a,a.size());
    for(int i:a){
        cout<<i<<" ";
    }
    return 0;
} 