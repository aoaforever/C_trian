#include "ListNode.h"
#include <cstdio>
using namespace std;


class Solution {
private:
ListNode* successor = NULL;
ListNode* reverseN(ListNode* head, int n){
    return reverse(head,n);
}

ListNode* reverse(ListNode* head, int n ){//递归
    //4.
    if(n==1){
        successor = head->next;
        return head;
    }

    //1.不管，直接去到第n个 5.返回新的头节点
    ListNode* last = reverse(head->next,n-1);

    //2.假如已经退刀第一个
    head->next->next = head;
    
    //3.头节点的下一个节点应该连接到第n个节点的下一个节点,因此需要记录第n个节点的下一个节点
    head->next = successor;
    return last;
}
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        //2.到第left个节点在进行反转
        if(left==1){
            return reverseN(head,right);
        }

        //1.假如已经推到第一个节点了
        head->next = reverseBetween(head->next,left-1,right-1);
        return head;
    }
};