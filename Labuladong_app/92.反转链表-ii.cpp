/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
 *
 * https://leetcode-cn.com/problems/reverse-linked-list-ii/description/
 *
 * algorithms
 * Medium (55.30%)
 * Likes:    1247
 * Dislikes: 0
 * Total Accepted:    285.3K
 * Total Submissions: 515.9K
 * Testcase Example:  '[1,2,3,4,5]\n2\n4'
 *
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left  。请你反转从位置 left 到位置 right 的链表节点，返回
 * 反转后的链表 。
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：head = [1,2,3,4,5], left = 2, right = 4
 * 输出：[1,4,3,2,5]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：head = [5], left = 1, right = 1
 * 输出：[5]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 链表中节点数目为 n
 * 1 
 * -500 
 * 1 
 * 
 * 
 * 
 * 
 * 进阶： 你可以使用一趟扫描完成反转吗？
 * 
 */

// @lc code=start
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        //找到left前一个，right
        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;
        prev->next = head;
        ListNode* cur = prev->next;
        for(int i=0;i<left-1;i++){
            prev = prev->next;
        }
        cur = prev->next;
        
        //现在prev指向left前一个，cur指向left
        //还需要一个指向right
        ListNode* rightnode = cur;
        for(int i=0;i<right-left;i++){
            rightnode = rightnode->next;
        }
        
        //现在rightnode指向right
        ListNode* rightright = rightnode->next;
        //断开连接
        prev->next = nullptr;
        rightnode->next = nullptr;

        reverseList(cur);
        prev->next = rightnode;
        cur->next = rightright;
        return dummy->next;//!!!!!!!
    }
    ListNode* reverseList(ListNode* head){
        ListNode* prev=nullptr,*cur=head,*next;
        while(cur){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
// @lc code=end

