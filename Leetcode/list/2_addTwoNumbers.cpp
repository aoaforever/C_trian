
#include <vector>
#include <iostream>
#include <algorithm>
#include "ListNode.h"
using namespace std;


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int jinwei =0;
        
        ListNode* res= new ListNode();
        ListNode* i=l1,*j=l2,*k=res;
        while (i||j||jinwei>0)
        {
            //巧妙的合并
            int add = jinwei;
            if(i){
                add += i->val;
                i=i->next;
            }
            if(j){
                add += j->val;
                j =j->next;
            }
            // int add = i->val+j->val; 
            // add += jinwei;

            jinwei = add/10;//不同为1.
            
            k->next=new ListNode(add%10);
            k=k->next;
            
        }
        // while(i){
        //     int add = i->val; 
        //     add += jinwei;
        //     jinwei = add/10;//不同为1.
            
        //     k->next=new ListNode(add%10);
        //     k=k->next;
        //     i=i->next;

        // }
        // while(j){
        //     int add = j->val; 
        //     add += jinwei;
        //     jinwei = add/10;//不同为1.
            
        //     k->next=new ListNode(add%10);
        //     k=k->next;

        //     j=j->next;
        // }
        // if(jinwei==1){
        //     k->next=new ListNode(1);
        // }
        return res->next;
    }
};

