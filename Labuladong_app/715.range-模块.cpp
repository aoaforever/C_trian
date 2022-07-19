/*
 * @lc app=leetcode.cn id=715 lang=cpp
 *
 * [715] Range 模块
 *
 * https://leetcode.cn/problems/range-module/description/
 *
 * algorithms
 * Hard (43.52%)
 * Likes:    150
 * Dislikes: 0
 * Total Accepted:    9.5K
 * Total Submissions: 18.5K
 * Testcase Example:  '["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]\n' +
  '[[],[10,20],[14,16],[10,14],[13,15],[16,17]]'
 *
 * Range模块是跟踪数字范围的模块。设计一个数据结构来跟踪表示为 半开区间 的范围并查询它们。
 * 
 * 半开区间 [left, right) 表示所有 left <= x < right 的实数 x 。
 * 
 * 实现 RangeModule 类:
 * 
 * 
 * RangeModule() 初始化数据结构的对象。
 * void addRange(int left, int right) 添加 半开区间 [left,
 * right)，跟踪该区间中的每个实数。添加与当前跟踪的数字部分重叠的区间时，应当添加在区间 [left, right)
 * 中尚未跟踪的任何数字到该区间中。
 * boolean queryRange(int left, int right) 只有在当前正在跟踪区间 [left, right)
 * 中的每一个实数时，才返回 true ，否则返回 false 。
 * void removeRange(int left, int right) 停止跟踪 半开区间 [left, right)
 * 中当前正在跟踪的每个实数。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入
 * ["RangeModule", "addRange", "removeRange", "queryRange", "queryRange",
 * "queryRange"]
 * [[], [10, 20], [14, 16], [10, 14], [13, 15], [16, 17]]
 * 输出
 * [null, null, null, true, false, true]
 * 
 * 解释
 * RangeModule rangeModule = new RangeModule();
 * rangeModule.addRange(10, 20);
 * rangeModule.removeRange(14, 16);
 * rangeModule.queryRange(10, 14); 返回 true （区间 [10, 14) 中的每个数都正在被跟踪）
 * rangeModule.queryRange(13, 15); 返回 false（未跟踪区间 [13, 15) 中像 14, 14.03, 14.17
 * 这样的数字）
 * rangeModule.queryRange(16, 17); 返回 true （尽管执行了删除操作，区间 [16, 17) 中的数字 16
 * 仍然会被跟踪）
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= left < right <= 10^9
 * 在单个测试用例中，对 addRange 、  queryRange 和 removeRange 的调用总数不超过 10^4 次
 * 
 * 
 */

// @lc code=start
// class RangeModule {
// public:
//     vector<vector<int>> range;
//     RangeModule() {

//     }
    
//     void addRange(int left, int right) {

//         //判断有无重叠，相交区间
//         if(range.size()==0){
//             range.emplace_back(vector<int>{left,right});
//             return;
//         }
//         //应该先插入，再去重
//         range.emplace_back(vector<int>{left,right});
//         sort(range.begin(),range.end(),[](vector<int>&a, vector<int>&b){
//             if(a[0]==b[0]) return a[1]>b[1];
//             return a[0]<b[0];
//         });
//         vector<vector<int>> tmp;
        
//         int l = range[0][0], r = range[0][1];
//         tmp.emplace_back(vector<int>{l,r});
//         for(int i=1;i<range.size();i++){
//             int cur_l = range[i][0], cur_r = range[i][1];
//             if(cur_r<l||cur_l>r){
//                 //不重叠
//                 l = cur_l;
//                 r = cur_r;
//                 tmp.emplace_back(vector<int>{cur_l,cur_r});
                
//             }
//             else{
//                 //相交
//                 l = min(cur_l,l);
//                 r = max(cur_r,r);
//                 tmp.back()[0] = l;
//                 tmp.back()[1] = r;
//             }

//         }

//         range = tmp;
//         cout<<"after add:"<<endl;
//         for(auto& r:range){
//             cout<<r[0]<<" "<<r[1]<<endl;
//         }
//         cout<<endl<<endl;
//     }
    
//     bool queryRange(int left, int right) {
//         for(vector<int>& r:range){
//             if(left>=r[0]&&right<=r[1]){
//                 return true;
//             }
//         }
//         return false;
//     }
    
//     void removeRange(int left, int right) {
//         sort(range.begin(),range.end(),[](vector<int>&a, vector<int>&b){
//             if(a[0]==b[0]) return a[1]>b[1];
//             return a[0]<b[0];
//         });
//         vector<vector<int>> tmp;
//         for(vector<int>& r:range){
//             if(right<=r[0]||left>=r[1]){
//                 tmp.emplace_back(r);
//                 continue;
//             }
//             else if(left==r[0]&& right==r[1]){
//                 continue;
//             }
//             else if(left>=r[0]&&right<=r[1]){
//                 if(left==r[0]){
//                     tmp.emplace_back(vector<int>{right,r[1]});    
//                     continue;
//                 }
//                 if(right==r[1]){
//                     tmp.emplace_back(vector<int>{r[0],left});
//                     continue;    
//                 }
                
//                 tmp.emplace_back(vector<int>{r[0],left});
//                 tmp.emplace_back(vector<int>{right,r[1]});
//             }

//         }
//         range = tmp;
//         cout<<"after remove:"<<endl;
//         for(auto& r:range){
//             cout<<r[0]<<" "<<r[1]<<endl;
//         }
//         cout<<endl;
//     }
// };


/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class RangeModule {
public:
    int N = 1e9, cnt =1;
    const static int M =500000;
    class Node{
    public:
        bool cover;
        int left;
        int right;
        int add;
        Node(){
            cover = false;
            add=0;
            left = 0;
            right = 0;
        }
        
    };
    Node* root = new Node[M];

    RangeModule() {
        // root.resize(M);
        // cout<<root.size()<<endl;
        // cout<<root[1000]->cover<<endl;
    }
    // Node* root[M] = new Node()[M];

    void addRange(int left, int right) {
        //1 <= left < right <= 10e9
        update(1,1,N,left,right-1,1);
    }
    
    bool queryRange(int left, int right) {
        return query(1,1,N,left,right-1);
    }
    
    void removeRange(int left, int right) {
        update(1,1,N,left,right-1,-1);
    }


    
    void update(int node, int start, int end, int l , int r, int val){
        //更新[l,r]区间的值，加val。
        //如果[l,r]完全包含 [start,end]，则直接更新[start,end]的node，设置add,并返回
        if(l<=start&&r>=end){
            root[node].cover = (val==1);
            root[node].add = val;
            return;
        }
        int mid = start + (end-start)/2;
        //先下推lazy标记，如果没有则什么也不做
        //左区间[l,mid], 右区间[mid+1,end]
        pushdown(node,mid-start+1, end-mid);
        //如果没有覆盖[start,end]区间，则要判断左右子树的交集，有交集则往下更新
        if(l<=mid) update(root[node].left,start,mid,l,r,val);
        if(r>mid) update(root[node].right,mid+1,end,l,r,val);
        pushup(node);

    }
    bool query(int node, int start,int end, int l ,int r){
        //查询[l,r]区间的和
        if(l<=start&& r>=end) return root[node].cover;

        int mid = start+ (end-start)/2;
        pushdown(node,mid-start+1,end-mid);
        bool ans=true;
        if(l<=mid) ans = ans && query(root[node].left,start,mid,l,r);
        if(r>mid) ans = ans && query(root[node].right,mid+1,end,l,r);
        return ans; //不需要加本节点的值！因为你都没命中全部区间。

    }
    void pushdown(int node, int leftNum, int rightNum){
        if(root[node].left==0) root[node].left = ++cnt;
        if(root[node].right==0) root[node].right = ++cnt;

        if(root[node].add ==0) return;
        root[root[node].left].cover = (root[node].add==1); 
        root[root[node].right].cover = (root[node].add==1);

        root[root[node].left].add = root[node].add;
        root[root[node].right].add = root[node].add;
        root[node].add =0;
    }
    inline void pushup(int node){
        root[node].cover  = root[root[node].left].cover && root[root[node].right].cover;
    }
};
// @lc code=end

