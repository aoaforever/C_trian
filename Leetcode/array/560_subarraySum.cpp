#include <vector>
#include <unordered_map>

using namespace std;

//超时
class Solution{

public:
    int subarraySum(vector<int>& nums, int k){
        // vector<int> preSum(nums.size()+1);
        unordered_map<int,int>  preSum;//前缀和，该前缀和出现的次数
        preSum[0] =1;

        int res =0, sum0_i =0;
        for(int i=0; i< nums.size();i++){
            sum0_i += nums[i];
            //这是我们想找的前缀和 nums[0..j];
            int sum0_j = sum0_i -k;

            //如果前面有这个前缀和，则直接更新答案
            if (preSum.find(sum0_j)!=preSum.end()){
                // res += preSum.find(sum0_j)->second;
                res += preSum[sum0_j];
            }
            //把前缀和nums[0..i]加入并记录出现次数
            // preSum[sum0_i] = preSum[sum0_i] + 1;
            preSum[sum0_i]++;

            // preSum[i+1] = preSum[i] + nums[i];
        }

        // int count =0;
        // for(int i=0; i < preSum.size();i++){
        //     for(int j =i+1; j<preSum.size();j++){
        //         if(k == preSum[j]-preSum[i]) ++count;
        //     }
        // }

        // return count;
        return res;

    }
};