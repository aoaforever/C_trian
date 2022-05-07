/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 *
 * https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (41.61%)
 * Likes:    7936
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 3.1M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：l1 = [0], l2 = [0]
 * 输出：[0]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * 输出：[8,9,9,9,0,0,0,1]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 每个链表中的节点数在范围 [1, 100] 内
 * 0 
 * 题目数据保证列表表示的数字不含前导零
 * 
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
// typedef struct ListNode{
//     int val;
//     ListNode* next;
// }ListNode;

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
// @lc code=end

