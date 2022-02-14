//反转链表前 N 个节点
#include "ListNode.h"
#include <cstdio>

using namespace std;

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