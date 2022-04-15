
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> res;
        // sort(nums.begin(),nums.end());
        int dup =-1;
        int queshi = -1;
        for(int i =0;i<nums.size();i++){
            int index = abs(nums[i]) -1;
            //如果当前元素指向索引的数已经是负数了，那么就是当前元素就是重复的元素
            if(nums[index]<0) dup = abs(nums[i]);
            //将该元素指向的下标变成负数
            else nums[index] *= -1 ;
        }
        for(int i=0;i<nums.size();i++){
            if(nums[i]>0){
                queshi = i+1;
            }
        }

        return vector<int>({dup,queshi});
    }
    
};