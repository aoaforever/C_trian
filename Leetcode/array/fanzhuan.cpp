#include <vector>
#include <iostream>

using namespace std;

void fanzhuan(vector<int>&nums,int left , int right){
    //对下标为left,right 做翻转
    if(left<0||right>(nums.size()-1)){
        cout<<"out of subindex\n";
        exit(-1);
    }
    while (left < right)
    {
        swap(nums[left++],nums[right--]);
    }
    
}
int main(){
    vector<int> nums{-1,3,-5,2,-1,3};
    fanzhuan(nums,-1,5);
    for(auto& n : nums){
        cout<<n<<" ";
    }
    return 0;
}