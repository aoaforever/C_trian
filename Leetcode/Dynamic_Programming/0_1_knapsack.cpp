//背包问题 P466

// N =3, W =4
// wt = [2,1,3]
// val = [4,2,3]
#include <iostream>
#include <vector>

using namespace std;
int dp(int w, int i, vector<int>&wt, vector<int>& val);
int knapsack(int W, int N, vector<int>&wt, vector<int>& val){
    return dp(W,N,wt,val);
}
//dp代表： 前i个物品，在w容量下，能达到的最大价值。
//i:[1~N]  w:[1~W]
//i-1表示第i个物品
int dp(int w, int i, vector<int>&wt, vector<int>& val){
    if(i<1){
        return 0;
    }

    if(w-wt[i-1]<0){//看，又来了，先判断能不能装，不能装就直接继承上次的。
        return dp(w,i-1,wt,val);
    }
    else{
        //如果能装，那就两种选择，是不装还是装，看哪个价值更高。
        return max(dp(w,i-1,wt,val),
                   dp(w-wt[i-1],i-1,wt,val)+val[i-1]
                   );
    }
}

int main(){
    int N, W;
    cin>>N>>W;

    vector<int> wt(N,0);
    vector<int> val(N,0);

    for(int i=0;i<N;i++){
        cin>>wt[i];
    }
    for(int i=0;i<N;i++){
        cin>>val[i];
    }

    cout<<knapsack(W,N,wt,val)<<endl;

    return 0;
}

