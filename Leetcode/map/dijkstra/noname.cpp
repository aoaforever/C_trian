/*作者：牛客510380970号
链接：https://www.nowcoder.com/discuss/420502?type=all&order=time&pos=&page=1&ncTraceId=&channel=-1&source_id=search_all_nctrack
来源：牛客网
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<map>
#include<cmath>
#include<set>
#include<string>
#include<iostream>

using namespace std;

/*
第三题、大概是个求最短路径的问题，给的是有向图，城市1~N，然后还有过路费，问只带了k个硬币的情况下，找到从城市1到城市N的最短路径，如果不存在通路，打印-1。
*/

struct edge
{
    int dst, cost, len;
    edge(int d = 0, int c = 0, int l = 0) { 
        dst = d; cost = c; len = l; 
        }
};

vector<vector<edge>> g;
bool vis[1000];
long long best = 100000000;
void work(int now, int left, int len,int n)
{
    if (left < 0) return;
    if (now == n)
    {
        if (len < best) best = len; 
        return;
    }
    if (vis[now]) return;
    vis[now] = true;
    for (edge e : g[now])
    {
        int dst = e.dst;
        work(dst,left-e.cost,len+e.len,n);
    }
    vis[now] = false;
}


int main()
{
    int k, n, r;
    scanf("%d%d%d", &k, &n, &r);
    g.resize(n + 1);


    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < r; i++)
    {
        int s, d, c, l;
        scanf("%d%d%d%d", &s, &d, &l, &c);
        g[s].push_back(edge(d, c, l));//s点出发，到d点，要花费c， 路径长为l
    }
    work(1, k, 0, n);//从1出发，到n， 有k钱， 路径长初始为0
    if (best == 100000000) best = -1;
    printf("%lld\n", best);
    return 0;
}