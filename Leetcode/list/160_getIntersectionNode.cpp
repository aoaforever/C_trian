#include <cstdio>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *q1 = headA;
        ListNode *q2 = headB;

        while (q1!=q2)
        {
            if(q1==NULL){
                q1=headB;
            }
            else {
                q1 = q1->next;
            }

            if(q2 == NULL){
                q2 = headA;
            }
            else {
                q2 = q2->next;
            }

        }
        return q1;
        
    }
};