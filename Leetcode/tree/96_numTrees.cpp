class Solution {
public:
    //为什么是n+1，因为索引是从1开始，0废了，所以索引范围是[1~n],一个n个。
    int numTrees(int n) {
        vector<vector<int>> meo(n+1,vector<int>(n+1,0));
        return count(1,n,meo);
    }
    int count(int lo, int hi,vector<vector<int>>& meo){
        
        int res=0;
        if(lo>hi){
            return 1;
        }
        if(meo[lo][hi]!=0) return meo[lo][hi];

        //以i为根的情况有多少种？所以在for外面初始化res。
        for(int i=lo;i<=hi;i++){
            int left = count(lo,i-1,meo);
            int right = count(i+1,hi,meo);
            //确定当前节点做什么
            //以i为根，对左右子树进行排列组合
            res += left*right;//因为有很多根，所以累加
        }
        //为什么是for外面更新备忘录？返回res？
        //meo更新的是当前lo~hi的值。所以在外面，而res记录的是lo~hi一共有多少种。
        meo[lo][hi] = res;
        return res;
        
        //先确定返回值
    }
};

class Solution {
public:
    vector<vector<int>> memo;
    int numTrees(int n) {
        memo = vector<vector<int>>(n+1,vector<int>(n+1,-1));
        return build(1,n);
    }
    int build(int lo, int hi){
        //[lo,hi]构建bST的个数
        if(lo>hi) return 1;//空集也是一种情况
        if(memo[lo][hi]!=-1) return memo[lo][hi]; 
        int res =0;
        for(int i=lo;i<=hi;i++){
            int left = build(lo,i-1);
            int right = build(i+1,hi);
            //选用当前位置i，则左区间就是左子树，右区间就是右子树。
            res += left*right;//所有i遍历完，每个元素都成为根了，就得到最终的答案。
        }
        memo[lo][hi] =res;
        return res;
    }
};