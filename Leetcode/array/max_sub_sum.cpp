#include <iostream>
#include <vector>
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
int zichuanhe(vector<int>& nums){
    int res =0; 
    int sum = nums[0];

    for(int i =0; i<nums.size()-1;i++){
        sum = max(nums[i+1],sum+nums[i+1]);
        res = max(res,sum);
    }
    return res;
}


int fanzhuanyici(vector<int>& nums){
    int res=0;
    for(int i=0;i<nums.size();i++){
        for(int j=i;j<nums.size();j++){
            fanzhuan(nums,i,j);
            int n = zichuanhe(nums);
            res = max(res, n);
            //撤销翻转
            fanzhuan(nums,i,j);
        }

    }
    cout<<res;
    return res;
}

int main(){
    //我有一个数组，可以进行翻转。求这个数组的最大字串和
    vector<int> nums{-1,-1,5,-2,1,-5};
    // vector<vector<int>> res = permute(nums);
    fanzhuanyici(nums);
    return 0;
}