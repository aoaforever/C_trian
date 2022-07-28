
/*
实现一个 MyCalendar 类来存放你的日程安排。如果要添加的时间内不会导致三重预订时，则可以存储这个新的日程安排。

MyCalendar 有一个 book(int start, int end)方法。它意味着在 start 到 end 时间内增加一个日程安排，注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，  start <= x < end。

当三个日程安排有一些时间上的交叉时（例如三个日程安排都在同一时间内），就会产生三重预订。

每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致三重预订，返回 true。否则，返回 false 并且不要将该日程安排添加到日历中。

请按照以下步骤调用MyCalendar 类: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

 

示例：

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
解释： 
前两个日程安排可以添加至日历中。 第三个日程安排会导致双重预订，但可以添加至日历中。
第四个日程安排活动（5,15）不能添加至日历中，因为它会导致三重预订。
第五个日程安排（5,10）可以添加至日历中，因为它未使用已经双重预订的时间10。
第六个日程安排（25,55）可以添加至日历中，因为时间 [25,40] 将和第三个日程安排双重预订；
时间 [40,50] 将单独预订，时间 [50,55）将和第二个日程安排双重预订。
 

提示：

每个测试用例，调用 MyCalendar.book 函数最多不超过 1000次。
调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/my-calendar-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

class MyCalendarTwo {
public:
    MyCalendarTwo() {

    }
    
    bool book(int start, int end) {
        if(query(0,0,1e9,start,end-1)>=2) return false;
        update(0,0,1e9,start,end-1,1);
        return true;
    }
    //

    //给[start,end)区间都就上1，那就是给[start,end-1]区间加上1
    //如果区间==2，说明不能再加了，返回false‘
    class node{
        public:
        int val;
        int lazy;
        int left;//左节点
        int right;//右节点
        node(){
            val=0;
            lazy=0;
            left=-1;
            right=-1;
        }
    };
    const int m = 1e5;
    node* tree = new node[m];
    int count=1;
    void update(int p ,int start,int end,int l,int r, int val){
        //给[l,r]区间加val.
        
        //如果[l,r]包含[start,end]，则直接更新
        if(l<=start&&r>=end){
            //给这个区间每个点+val
            //那么这个区间的总值就是(r-l+1)*val
            tree[p].val += val;
            tree[p].lazy += val; // 细节
            return ;
        }
        //首先下推lazy？
        int mid = start + (end-start)/2;
        down(p,start,end,mid);
        //然后分区间
        if(l<=mid){ 
            update(tree[p].left,start,mid,l,r,val);
        }
        if(r>mid){
            update(tree[p].right,mid+1,end,l,r,val);
        }
        //向上更新
        up(p);
    }
    void down(int p,int start,int end, int mid){
        if(tree[p].left==-1) tree[p].left = ++count;
        if(tree[p].right==-1) tree[p].right = ++count;
        if(tree[p].lazy==0) return;
        //将左区间全部加lzay，将右区间全部加lazy，本区间的lazy置零
        tree[tree[p].left].val += (tree[p].lazy);
        tree[tree[p].left].lazy += tree[p].lazy;

        tree[tree[p].right].val += (tree[p].lazy);
        tree[tree[p].right].lazy += tree[p].lazy;

        tree[p].lazy =0;
    }
    void up(int p){
        tree[p].val = max(tree[tree[p].left].val,tree[tree[p].right].val);
    }

    int query(int p, int start, int end, int l, int r){
        if(l<=start&&r>=end){return tree[p].val;}
        int mid = start+ (end-start)/2;
        down(p,start,end,mid);
        int ans=0;
        if(l<=mid) ans = max(ans,query(tree[p].left,start,mid,l,r));
        if(r>mid) ans =max(ans,query(tree[p].right,mid+1,end,l,r));
        return ans;
    }

};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */