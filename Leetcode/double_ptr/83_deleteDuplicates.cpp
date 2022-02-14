#include <iostream>

using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL){
            return head;
        }
        ListNode *slow=head, *fast=head;
        while(fast!=NULL){
            if(fast->val!=slow->val){
                // slow = slow->next;
                // slow->val = fast->val;

                //或者这种写法
                slow->next = fast;
                slow = slow->next;
            }
            fast = fast->next;
        }

        //截断
        slow->next = NULL;
        return head;
    }
};
 