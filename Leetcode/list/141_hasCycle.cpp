#include <cstdio>
using namespace std;
/*给你一个链表的头节点 head ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 true 。 否则，返回 false 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/linked-list-cycle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast!=NULL&&fast->next!=NULL)
        {
            fast=fast->next->next;
            slow = slow->next;
            if(fast == slow){
                break;
            }
        }
        //你不知道是break还是fast走到了NULL
        if(fast==NULL||fast->next==NULL){
            return false;
        }

        //不然就是有环
        return true;
        
    }
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast!=NULL&&fast->next!=NULL)
        {
            fast=fast->next->next;
            slow = slow->next;
            if(fast == slow){
                //其实这里就表示有环了
                return true;
            }
        }
        return false;
        
    }
};