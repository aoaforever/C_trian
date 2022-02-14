
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//删除倒数第n个节点，先找到倒数第n+1个节点。
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *p=dummy, *q=dummy;
        for(int i = 0; i<n+1;i++){
            q = q->next;
        }

        while (q)
        {
            q=q->next;
            p=p->next;
        }

        p->next = p->next->next;
        return dummy->next;
        
    }
};