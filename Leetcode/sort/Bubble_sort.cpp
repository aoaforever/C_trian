#include <vector>
#include <iostream>

using namespace std;

void bubble_sort(vector<int> &nums, int n ){
    bool swapped;
    for(int i =0;i<n-1;i++){
        swapped = false;
        for(int j=n-1;j>i;--j){
            if(nums[j]<nums[j-1]){
                swap(nums[j],nums[j-1]);
                swapped=true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

int main(){
    vector<int> a{1,2,3,9,8,7,6,5,4,3};
    bubble_sort(a,a.size());
    for(int i:a){
        cout<<i<<" ";
    }
    return 0;
} 