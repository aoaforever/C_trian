#include <vector>
using namespace std;

/*给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按 任何顺序 返回答案。*/

class Solution{
public:
    vector<vector<int>> combine(int n, int k ){
        //数组范围1~n;
        //从中选k个数
        vector<vector<int>> ans;
        vector<int> comb(k);

        int count = 0 ; 
        backtrack(ans,comb,1,n,count,k);

        return ans;
    }

    void backtrack(vector<vector<int>>& ans, vector<int> &comb, int pos,int n ,int count, int k){
        //递归停止的条件comb数组中满了2个数.
        if(k==count){
            ans.push_back(comb);
            return ;
        }

        for(int i =pos; i<= n ; i++){
            comb[count++]=i;//i就是1~n其中一个数
            backtrack(ans,comb,i+1,n,count,k);//是i+1
            --count;
        }

    }
};