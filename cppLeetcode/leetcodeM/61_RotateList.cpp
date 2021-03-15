/*
61. Rotate List

Given the head of a linked list, rotate the list to the right by k places.

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Example 2:


Input: head = [0,1,2], k = 4
Output: [2,0,1]
 

Constraints:

The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109

*/



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
class Solution {

    struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /*
        061.Rotate-List
        此题对于链表的操作包括：

        1. 确定链表的总长度Len，注意如果Len==0时的处理（此时可以顺便记录末尾节点end）
        2. 确定实际需要旋转的次数 k=k%Len
        3. 令p从头指针前进 Len-k+1 步，就到了断开链表的位置。
        4. 将p->next作为新的head，原本的end之后指向原本的head，再把p的next指向NULL，
    */
    ListNode* rotateRight(ListNode* head, int k) 
    {
        if (head==0) return nullptr;
        ListNode* end = head;
        int count = 1;        
        while (end->next != nullptr)
        {
            count++;
            end = end->next;
        }
        int t = count - k % count - 1;

        ListNode* p = head;
        for (int i=0; i<t; i++)
            p = p->next;
        end->next = head;
        ListNode* ret = p->next;
        p->next = nullptr;
        return ret;        
    }
 
public:
    ListNode* doit_link(ListNode* head, int k) {
        
        if (!head) return head;
        
        int total = 0;
        ListNode *cur = head;
        while (cur) {
            total++;
            cur = cur->next;
        }
        
        k %= total;
        
        if (k == 0) return head;
        
        ListNode *slow = head, *fast = head;
        
        while (fast->next) {
            
            if (--k < 0) slow = slow->next;
                
            fast = fast->next;
        }
        
        ListNode* res = slow->next;
        slow->next = nullptr;
        fast->next = head;
        
        return res;
    }
};