#include <iostream>
#include <vector>
using namespace std;

int zichuanhe(vector<int>& nums){
    int res =0; 
    int sum = nums[0];

    for(int i =0; i<nums.size()-1;i++){
        sum = max(nums[i+1],sum+nums[i+1]);
        res = max(res,sum);
    }
    return res;
}

int main(){
    
}