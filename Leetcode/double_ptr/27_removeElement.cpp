#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size()==0){
            return 0;
        }

        int slow =0, fast =0;
        while(fast<nums.size()){
            if(nums[fast] != val){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }

        return slow;//注意这里
    }
};