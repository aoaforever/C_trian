//https://www.nowcoder.com/questionTerminal/0d939e874a004f449a370aca1346dd5c?answerType=1&f=discussion

#include <vector>
#include <limits.h>
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 301;
vector<int> v;//存节点值,这里不能初始化为0.
int memo[maxn][maxn][maxn];

int dp(int l, int r, int father){
    if(l>r) return 0;
    if(memo[l][r][father]!=-1) return memo[l][r][father];
    
    int ret =INT_MAX;
    for(int i=l;i<=r;i++){//这么多种情况能够做i根
    //经过左右遍历后，获得了左边路径数和右边路径数
    int left = dp(l,i-1,i);
    int right = dp(i+1,r,i);
    //当前节点做什么,获取当前节点的路径和。
    //二叉树的总开销即每条边的开销之和
    //每条边的开销为其两端节点权值的乘积
    //在所有可能的二叉树中，总开销最小的二叉树被称为最优二叉树
    cout<<"left "<<left<<endl;
    ret = min(ret, left + right + v[i]*v[father]);//顶部根节点的边开销为0.
    }
    cout<<"ret:"<<ret<<endl;
    //每条边的意思就是返回值两边都要咯
    memo[l][r][father] = ret;
    return ret;
    
}

int main(){
    int n;
    cin>>n;
    v.push_back(0);//放入假根
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    memset(memo,-1,sizeof(memo));
    int ans = dp(1,n,0);//0位置做father
    cout<<ans;

    return 0;
}