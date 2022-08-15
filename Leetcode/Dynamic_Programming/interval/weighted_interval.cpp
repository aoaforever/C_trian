/*
给定若干个工作的开始时间、结束时间和权重（可以理解成重要程度），求出能完成的最大的工作权重（尽可能地完成更重要的工作），当然必须满足各个工作相容。如以下三个工作：
              开始时间    结束时间    权重
工作1           0               3              4
工作2           5               6              5
工作3           2               8             10
  由不带权重的区间调度方法，依次结束时间最早且相容的工作，这里就选出{1, 2}，能实现的最大权重是4+5=9。而显而易见，选择{3}权重可达到10，因此最早结束时间的贪心策略在带权重的区间调度问题里已不适用。

作者：小菜变大菜
链接：https://www.jianshu.com/p/3a1d5cecfbe5
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include <tuple>
using namespace std;

int find(vector<tuple<int,int,int>>& interval, int j){
    //找出与下标j不冲突的最大下标i
    int start_j = get<0>(interval[j]);
    for(int i=j-1;i>=0;i--){
        int& end_i = get<1>(interval[i]);
        if(end_i<=start_j) return i;
    }
    return 0;
}

void help(vector<tuple<int,int,int>>& interval){
    sort(interval.begin(),interval.end(),[](tuple<int,int,int>&a, tuple<int,int,int>& b){
        return get<1>(a) < get<1>(b);
    });

    vector<int> dp(interval.size()+1);
    dp[0] =0;//0个任务下，权重最大值为0

    for(int i=1;i<dp.size();i++){
        dp[i] = max(dp[i-1], dp[find(interval,i)]+ get<2>(interval[i]));
    }
    cout<<dp[interval.size()]<<endl;

}



int main(int argc, char const *argv[])
{
    int n;//几个任务
    cin>>n;
    vector<tuple<int,int,int>> interval(n);
    for(int i=0;i<n;i++){
        int start,end,weight;
        cin>>start>>end>>weight;
        interval[i] = make_tuple(start,end,weight);
    }

    help(interval);

    return 0;
}
