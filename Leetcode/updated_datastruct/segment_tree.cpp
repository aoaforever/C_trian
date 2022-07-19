#include<iostream>
#include<vector>
#include<algorithm>
#include <memory>
using namespace std;
// https://blog.csdn.net/m0_57298796/article/details/125374901
/*这个模板试左闭右闭， 如果需要左闭右开，不需要该模板，在接口处传l, r-1 就能实现[l,r)*/

//线段树，首先要构建数的节点数据结构
class Node{
public:
    int add;
    int ls,rs;
    int val;
    Node():add(0),ls(0),rs(0),val(0){}

    //ls,rs分别代表节点node的左右孩子节点的下标
    //val代表当前节点的val
    //add代表懒标记
};

int N = 1e9 , M = 120010, cnt =1;
//cnt代表当前节点的下标，1表示根节点的下标为1.
//M是动态开点的大小，是不断试出来的，小了会堆溢出、大了会超时。所以要不断的试。像个sb一样

Node* tr = new Node[M];

int query(int root, int start,int end, int l, int r){
    if(l<=start&& r>=end){
        //完全命中该区间，直接返回
        return tr[root].val;
    }
    //动态创建节点
    lazyCreate(root);
    //下推标记，如果有的话
    pushdown(root,end-start+1);//传入当前[start,end]的节点个数
    int mid = start + (end-start)/2, ans = 0 ;
    if(l<=mid) ans  = query(tr[root].ls,start,mid,l,r);
    if(r>=mid+1) ans += query(tr[root].rs,mid+1,end,l,r);
    return ans;

}

void update(int root, int start, int end , int l ,int r, int val){
    if(l<=start&&r>=end){
        tr[root].val += (r-l+1)*val;
        tr[root].add = val;
        return ;
    }
    lazyCreate(root);
    pushdown(root,end-start+1);
    int mid = start + (end-start)/2;
    if(l<=mid) update(tr[root].ls,start,mid,l,r,val);
    if(r>mid) update(tr[root].rs,mid+1,end,l,r,val);
    pushUp(root);
}

void pushUp(int root){
    tr[root].val = tr[tr[root].ls].val + tr[tr[root].rs].val;
}
void lazyCreate(int root){
    if(tr[root].ls==0){
        tr[root].ls = ++cnt;
        // tr[tr[root].ls] = new Node();// 不需要再new了呀，因为你建树的时候已经全部new出来了
    }
    if(tr[root].rs==0){
        tr[root].rs = ++cnt;
    }
}
void pushdown(int root, int len){
    tr[tr[root].ls].add += tr[root].add;
    tr[tr[root].rs].add += tr[root].add;

    tr[tr[root].ls].val += (len - len/2)*tr[root].add; //让左孩子的区间每个点都+add， 那么这个区间的值val += （区间长度）*add；
    tr[tr[root].rs].val += (len/2)*tr[root].add;

    tr[root].add =0;
}
