#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//使用优先队列存储K个链表，在一一弹出
class Solution {
private:
    struct cmp{
        bool operator()(ListNode* a, ListNode* b){
            return a->val>b->val; //greater，降序，返回最小值
        }
    };
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,cmp> q;
        for(ListNode* i : lists){
            while (i!=NULL)
            {
                q.push(i);
                i=i->next;
            }
        }
        ListNode* ans = new ListNode(-1);
        ListNode* p = ans;
        while (!q.empty())
        {
            ListNode* tmp = q.top();
            q.pop();
            // cout<<tmp->val<<" ";
            p->next=tmp;
            p=p->next;

        }
        p->next = nullptr;//没有这个会报错。
        
        return ans->next;
    }
};

/*优先队列 pq 中的元素个数最多是 k，所以⼀次 top() 或者 push() ⽅法的时间复杂度是 O(logk)；所有的链表
节点都会被加⼊和弹出 pq，所以算法整体的时间复杂度是 O(Nlogk)，其中 k 是链表的条数，N 是这些链表
的节点总数。*/
class Solution {
private:
    struct cmp{
        bool operator()(ListNode* a, ListNode* b){
            return a->val>b->val; //greater，降序，返回最小值
        }
    };
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,cmp> q;
        for(ListNode* head : lists){
            //只把头节点放进优先队列中
            if(head!=NULL){
                q.push(head);
            }
        }

        ListNode* ans = new ListNode(-1);
        ListNode* p = ans;

        //类似广度优先搜索，搜到该节点后，把后续的节点放进队列
        while (!q.empty())
        {
            ListNode* tmp = q.top();
            if(tmp->next!=NULL){
                q.push(tmp->next);
            }
            q.pop();
            // cout<<tmp->val<<" ";
            p->next=tmp;
            p=p->next;
        }
        // p->next = nullptr;//没有这个会报错。
        
        return ans->next;
    }
};