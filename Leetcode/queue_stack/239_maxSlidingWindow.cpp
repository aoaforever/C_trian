#include "MonotonicQueue.h"

#include <vector>

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> res;

        for(int i =0; i<nums.size(); ++i){
            if(i<k-1){
                window.push(nums[i]);
            }
            else{
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i-k+1]);
            }
        }

        return res;
    }
};