
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> nums;
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int index = -1;
        int size =0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==target){
                //如果是目标，记录这些下标
                size++;
                if(rand()%size==0){
                    index = i;
                }
            }
        }
        // cout<<index;
        return index;//返回下标啊操
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */

//省去了copy数组
class Solution {
public:
    vector<int>::iterator begin;
    vector<int>::iterator end;
    Solution(vector<int>& nums) {
        begin = nums.begin();
        end= nums.end();
    }
    
    int pick(int target) {
        int index = -1;
        int size =0;
        for(auto begin = this->begin;begin!=this->end;begin++){
            if(*begin==target){
                //如果是目标，记录这些下标
                size++;
                if(rand()%size==0){
                    index = begin-this->begin;
                }
            }
        }
        // cout<<index;
        return index;//返回下标啊操
    }
};


class Solution {
public:
    // vector<int> nums;
    vector<int>::iterator begin;
    vector<int>::iterator end;
    Solution(vector<int>& nums) {
        // this->nums = nums;
        begin = nums.begin();
        end = nums.end();
    }
    
    int pick(int target) {
        int size=0;
        int res;
        for(vector<int>::iterator i=begin;i!=end;i++){
            if(*i==target){
                size++;
                if(rand()%size==0) res=i-begin;
            }
        }
        return res;
    }
};