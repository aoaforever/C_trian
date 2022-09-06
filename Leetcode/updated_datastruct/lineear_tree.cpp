//线段树
//基本结构？
// 预先开好的树节点数组
// 一个开到哪的节点下标
// 懒标记
// 当前值？

// 函数：下推（）、查找（）、插入（）、

#include <bits/stdc++.h>
using namespace std;

struct node{
    int val;
    int lazy;
    int left,right;
    node(){
        val=0;
        lazy =0;
        left =-1;
        right =-1;
    }
};

class tri{
    public:
    
int n = 1e9 , m = 12500;
int cnt =1;
vector<node> tri_tree;
    tri(){
        tri_tree.resize(m);
    }

/*在一个大范围[start,end]中查询[l,r]区间的值*/
int query(int root, int start, int end ,int l, int r){
    if(l<=start&&r>=end){
        return tri_tree[root].val;
    }
    
    int mid = start + (end-start)/2;
    pushdown(root,start,mid,end);
    int ans=0;
    if(l<=mid) ans += query(tri_tree[root].left,start,mid,l,r);
    if(r>mid) ans += query(tri_tree[root].right,mid+1,end,l,r);

    return ans ;


}

void update(int root, int start, int end, int l ,int r , int v){
    if(l<=start&&r>=end){
        tri_tree[root].lazy += v;
        tri_tree[root].val += v;
        return;
    }

    int mid = start+(end-start)/2;
    pushdown(root,start,mid,end);
    if(l<=mid) update(tri_tree[root].left,start,mid,l,r,v);
    if(r>mid)  update(tri_tree[root].right,mid+1,end,l,r,v);
    pushup(root);
    return ;
}

void pushdown(int root, int start,int mid, int end){
    if(tri_tree[root].left==-1) tri_tree[root].left = ++cnt;
    if(tri_tree[root].right==-1) tri_tree[root].right = ++cnt;

    tri_tree[tri_tree[root].left].val += (mid-start+1)*tri_tree[root].lazy;
    tri_tree[tri_tree[root].right].val += (end-mid)*tri_tree[root].lazy;

    tri_tree[tri_tree[root].left].lazy += tri_tree[root].lazy;
    tri_tree[tri_tree[root].right].lazy += tri_tree[root].lazy;// +=

    tri_tree[root].lazy = 0;

}

void pushup(int root){
    tri_tree[root].val = tri_tree[tri_tree[root].left].val + tri_tree[tri_tree[root].right].val;
}

};
