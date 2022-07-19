    class Node{
    public:
        Node * left;
        Node * right;
        int val, add;
        Node(){
            val =0;
            add=0;
            left = nullptr;
            right = nullptr;
        }
        
    };
    Node* root = new Node();
    void update(Node* node, int start, int end, int l , int r, int val){
        //更新[l,r]区间的值，加val。
        //如果[l,r]完全包含 [start,end]，则直接更新[start,end]的node，设置add,并返回
        if(l<=start&&r>=end){
            node->val += (end-start+1)*val;//这个区间的长度*val + 本身 = 更新后的值。
            node->add = val;
            return;
        }
        int mid = start + (end-start)/2;
        //先下推lazy标记，如果没有则什么也不做
        //左区间[l,mid], 右区间[mid+1,end]
        pushdown(node,mid-start+1, end-mid);
        //如果没有覆盖[start,end]区间，则要判断左右子树的交集，有交集则往下更新
        if(l<=mid) update(node,start,mid,l,r,val);
        if(r>mid) update(node,mid+1,end,l,r,val);
        pushup(node);

    }
    int query(Node* node, int start,int end, int l ,int r){
        //查询[l,r]区间的和
        if(l<=start&& r>=end) return node->val;

        int mid = start+ (end-start)/2;
        pushdown(node,mid-start+1,end-mid);
        int ans=0;
        if(l<=mid) ans += query(node,start,mid,l,r);
        if(r>mid) ans += query(node,mid+1,end,l,r);
        return ans; //不需要加本节点的值！因为你都没命中全部区间。

    }
    void pushdown(Node* node, int leftNum, int rightNum){
        if(node->left==nullptr) node->left = new Node();
        if(node->right==nullptr) node->right = new Node();

        if(node->add ==0) return;
        node->left->val += node->add * leftNum; 
        node->right->val += node->add * rightNum;

        node->left->add += node->add;
        node->right->add += node->add;
        node->add =0;
    }
    void pushup(Node* node){
        node->val  = node->left->val + node->right->val;
    }








/********************************************/
//用数组来表示树
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