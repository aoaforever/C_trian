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
    ListNode* reverseList(ListNode* head) {
        return reverse(head);
    }

    ListNode* reverse(ListNode* head){
        //3.如果已经到达最后一个节点了
        if(head==NULL||head->next==NULL){
            return head;
        }

        //1.什么都别管，先去最后一个节点  4.用新的尾节点代替头节点
        ListNode* last = reverse(head->next);

        //2.假设已经退到首节点了
        head->next->next = head;
        head->next = NULL;

        //5.返回尾节点
        return last;
    }
};

//迭代的方法;
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //用三个指针
        ListNode* cur = head;
        ListNode* prev = NULL;//prev是cur的前一个节点
        //prev  cur  next
        while(cur){
            //肯定不能修改next的，改了还怎么迭代下去呢？
            ListNode* next = cur->next;//next是cur的下一个节点
            cur->next =prev;
            
            prev = cur;
            cur = next;
        }

        return prev;
    }


};
