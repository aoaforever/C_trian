#include <vector>
using namespace std;
//注意区间。！！i~j要表示这个区间是上了val个人，在j+1位置要-val。
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<int> ans(1000,0);//假设它就是差分数组
        for(vector<int>& trip : trips){
            int val = trip[0];
            int i = trip[1];//在第i位置上车
            int j = trip[2] -1 ;//在第j+1位置下车，但是i~j表示的是这个区间上了多少人

            ans[i] += val;
            if(j+1<ans.size()){
                ans[j+1] -= val;
            }
        }

        for(int i = 1; i<ans.size();i++){
            ans[i] = ans[i] + ans[i-1];
        }

        for(int i=0; i<ans.size();i++){
            if(ans[i]>capacity) return false;
        }
        return true;
    }
};