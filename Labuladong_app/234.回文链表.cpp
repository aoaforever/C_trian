/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        //将后面的逆转，然后和前面对比
        //偶数情况,fast=null,slow=后部分
        //奇数情况，1,2,3,2,1 ， fast->next = NULL
        // 1 2      3      2 1 
        //         null
        // 1 2    2  1
        ListNode* slow=head, *fast=head;
        while(fast||fast->next){
            slow= slow->next;
            fast=fast->next->next;
        }
        ListNode*p=head;
        // ListNode* middle;
        if(fast==nullptr){
            //偶数情况
        }
        else if(fast->next==nullptr){
            //奇数情况
            // middle = slow;
            slow=slow->next;
        }
        //翻转写这里
        ListNode* newhead = reverse(slow);
        // slow->next = middle;
        // middle->next = NULL;
        //拿p和slow比较
        ListNode* q = newhead;
        while(q){
            if(p->val==q->val){
                p=p->next;
                q=q->next;
            }
            else{
                return false;
            }
        }
        return true;
    }
    ListNode* reverse(ListNode* head){

        if(head->next){
            return head;
        }
        ListNode* last = reverse(head->next);
        head->next->next = head;
        head->next=nullptr; 
        return last;

    }
};