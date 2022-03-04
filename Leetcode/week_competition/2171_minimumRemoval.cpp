//https://leetcode-cn.com/problems/removing-minimum-number-of-magic-beans/
//请耐心看解析咯。。
//细节：0LL
//     LONG_LONG_MAX而不是INT_MAX,其实也可以是sum
//    乘法前转换long long 
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(),beans.end());
        long long sum =accumulate(beans.begin(),beans.end(),0LL);//累加器初始值
        long long ans=LONG_LONG_MAX;

        for(int i=0;i<beans.size();i++){
            long long tmp = sum - (long long)beans[i]*(beans.size()-i);
            if(tmp<ans){
                ans = tmp;
            }
        } 
        return ans;
    }
};