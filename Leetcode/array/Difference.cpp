//差分数组类
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Difference{
public:
    Difference(vector<int>&nums){
        diff.resize(nums.size());
        diff[0] = nums[0];
        for(int i=1;i<diff.size();i++){
            diff[i] = nums[i] - nums[i-1];
        }
    }
    void increment(int l,int r,int val){
        //给闭区间[l,r]增加val,下标l,r
        diff[l] += val;
        if(r+1<diff.size()){
            diff[r+1] -= val;
        }
    }
    vector<int> result(){//要返回复制，而不是引用，因为这个函数调用完，临时变量就被销毁了，引用个屁
        vector<int> num(diff.size());
        num[0] = diff[0];
        for(int i=1;i<num.size();i++){
            num[i] = num[i-1] + diff[i];
        }
        return num;
    }
private:    
    vector<int> diff;
};  