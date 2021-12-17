#include <iostream>
//https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/142-huan-xing-lian-biao-ii-jian-hua-gong-shi-jia-2/
//定理：相遇节点到环形入口节点的距离= 头节点到环形入口节点的距离！！！！
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr){}
};

class Solution{
public:
    ListNode *detectCycle(ListNode* head){
        ListNode* slow = head, *fast = head;//快慢指针
        //判断是否存在环路
        do{
            if(!fast || !fast->next){
                return nullptr;
            }

            fast= fast->next->next;
            slow=slow->next;
        } while(fast!=slow);

        //跳出了循环表明存在，如果存在，查找环路节点
        fast = head;
        while(fast!=slow){
            slow=slow->next;
            fast=fast->next;
        }

        return fast;



    }
};