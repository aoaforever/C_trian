#include <vector>
using namespace std;

class NumArray{
private:
    // vector<int> nums;
    vector<int> preSum;//前缀和数组

public:
    //输入一个数组，构造前缀和
    NumArray(vector<int> nums){
        // this->nums = nums;
        int n = nums.size();
        //preSum[0] =0 ,便于计算累加和。
        preSum.resize(n+1);
        for(int i =0; i<n;i++){
            preSum[i+1] = preSum[i] + nums[i]; 
        }
    }

    //查询闭区间[left,right]的累加和
    int sumRange(int left, int right){
        return preSum[right+1] - preSum[left];
    }

};