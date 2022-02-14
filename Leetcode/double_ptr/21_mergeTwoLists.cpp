#include<cstdio>

using namespace std;


//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//记住一点，不要对val进行复制，请直接改变指针！
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //要新建一个ListNode节点给ans。
        ListNode *ans = new ListNode(-1) , *p3;
        if(list1==NULL && list2==NULL){
            return ans;
        }
        ListNode *p1 = list1;
        ListNode *p2 = list2;
        p3=ans;
        while (p1!=NULL && p2!=NULL)
        {
            
            if(p1->val<p2->val){
                //接p1
                p3->next = p1;
                p3 = p3->next;
                p1 = p1->next;
            }
            else{
                //接p2
                p3->next = p2;
                p3 = p3->next;
                p2 = p2->next;
            }

        }

        if(p1==NULL){
            //将p2剩下的全部连接上去
            p3->next = p2;
        }
        
        if(p2==NULL){
            //将p1剩下的全部连接上去
            p3->next =p1;
            
        }

        return ans->next;//头节点不要，因为是多余的-1
    }
};