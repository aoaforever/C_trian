
 //Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> arr;
    Solution(ListNode* head) {
        ListNode* p = head;
        while(p!=NULL){
            arr.push_back(p->val);
            p=p->next;
        }
    }
    
    int getRandom() {
        return arr[rand()%arr.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

//空间复杂度为o(1)
class Solution {
public:
    ListNode* head;
    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        ListNode* p=head;
        int res =-1, size =0;
        while(p!=NULL){
            size++;
            if(rand()%size == 0){
                //生成[0,size)的整数，这个整数=0的概率为1/size
                res = p->val;
            }
            p=p->next;
        }
        return res;
    }
};