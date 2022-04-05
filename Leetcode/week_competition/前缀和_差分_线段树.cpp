#include <vector>
#include <iostream>
#include <limits.h>
using namespace std;

int qiuhe_max(vector<int>& nums){
	int max_ = INT_MIN;//首先，等于自己
   	for(int i =0;i<nums.size();i++)
	{
        
        int j=1;
        int res=nums[i];
        while((i+j)<nums.size()){
            res+= nums[i+j];
            j++;
            max_ = max(max_,res);
        }
        
    }
    return max_;
}

void fanzhuan(vector<int>& nums, int l, int r){
    while(l<r){
        swap(nums[l],nums[r]);
        l++;
        r--;
    }
}

int digui_fanzhuan(vector<int>& nums){
    int max_he =INT_MIN;
    for(int i=0;i<nums.size();i++){
        for(int j=i;j<nums.size();j++){
            //先求和在翻转？先翻转在求和？
            //先求和在翻转再求和。然后撤销反转。
            int he = qiuhe_max(nums);
            //翻转
            fanzhuan(nums,i,j);
            he = max(he, qiuhe_max(nums));
            max_he = max(max_he,he);
            //撤销
            fanzhuan(nums,i,j);
        }
    }
    return max_he;
}

int main(){
    int n;
    cin>>n;
    vector<int> nums;
    for(int i=0;i<n;i++){
        int tmp;
        cin>>tmp;
        nums.push_back(tmp);
    }
    
    int max_ = digui_fanzhuan(nums);
    cout<<max_;
    return 0;
}