#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> memo;
    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k+1,vector<int>(n+1,-1));
        return dp(k,n);
    }
    //dp表示k个鸡蛋，在N个楼层的最坏情况下，刚好不碎的至少操作数
    //选择就是，你有这么N个楼层，选那一层去扔，得到的操作数最少。
    //蛋没碎，就去i+1~N层测，一共N-(i+1)+1高= N-1;  1~N-1刚好就是N-1高。
    //蛋碎了，就去1~i-1测。

    //为什么要找最坏情况？？
    //注意+1的位置，肯定是在dp后面
    int dp(int k,int N){
        if(N==0) return 0;
        if(k==1) return N;
        if(memo[k][N]!=-1) return memo[k][N];
        int res=INT_MAX;
        for(int i=1;i<=N;i++){
            res = min(res,
                    max(dp(k-1,i-1),dp(k,N-i))+1
                );
        }
        memo[k][N] = res;
        return memo[k][N];
    }
};

//上面超时，所以用二分。
class Solution {
public:
    vector<vector<int>> memo;
    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k+1,vector<int>(n+1,-1));
        return dp(k,n);
    }

    int dp(int k,int N){
        if(N==0) return 0;
        if(k==1) return N;
        if(memo[k][N]!=-1) return memo[k][N];
        int res=INT_MAX;
        int lo=1, hi=N;
        while(lo<=hi){//为什么取等号？因为搜索区间是左闭右闭，所以结束条件是lo=hi+1,代入区间就是[hi+1,hi]，可见为空集。
            int mid = lo+ (hi-lo)/2;
            int broken = dp(k-1,mid-1);//单调递减,错误，他是单调递增！！！
            int not_broken = dp(k,N-mid);//单调递增，错误，他是单调递减！！！
            //把mid当横坐标，当mid增大时，broken增大，not_broken减少。
            if(not_broken>broken){
                //什么时候，往上缩
                res = min(res,not_broken+1);
                lo = mid+1;
            }
            else if(not_broken<broken){
                //往上缩
                res = min(res,broken+1);
                hi = mid-1;
            }
            else {
                res = min(res,broken+1);
                hi = mid-1;
            }
        }
        memo[k][N] = res;
        return memo[k][N];
    }
};