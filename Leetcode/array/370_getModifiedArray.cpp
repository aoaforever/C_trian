#include <vector>
#include <iostream>

using namespace std;

class Solution{
private:
    vector<int> diff;
    
public:
    //输入一个初始数组，区间操作将在这个数组上进行
    void Difference(vector<int>& nums){
        diff.resize(nums.size());
        diff[0]=nums[0];
        for(int i=1;i<diff.size();i++){
            diff[i] = nums[i]-nums[i-1];
        }
    }

    //给闭区间[i,j]增加val（可以是负数）
    void increment(int i , int j , int val){
        diff[i] += val;
        if(j+1<diff.size()){
            diff[j+1] -= val;
        }
    }

    //返回结果数组
    vector<int> result(){
        vector<int> res(diff.size());

        //根据差分数组构造结果数组
        res[0]=diff[0];
        for(int i =1; i<diff.size();i++){
            res[i] = res[i-1]+ diff[i];
        }
        return res;
    }

    vector<int> getModifiedArray(int length, vector<vector<int>> updates){
        //nums 初始化为全0
        vector<int> nums (length,0);
        // for(auto i : nums){
        //     cout<<i<<" ";
        // }
        Difference(nums);//会构建diff

        for(vector<int> update : updates){
            int i = update[0];
            int j =update[1];
            int val =update[2];
            increment(i,j,val);
        }

        nums=result();

        return nums;
    }
};

int main(){
    Solution solution;
    vector<vector<int>> updates{{1,3,2},{2,4,3},{0,2,-2}};
    auto nums = solution.getModifiedArray(5,updates);
    for(auto & i : nums){
        cout<<i<<" ";
    }
    return 0;
}