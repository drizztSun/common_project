/*
369. Plus One Linked List

Given a non-negative integer represented as a linked list of digits, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list.

 

Example 1:

Input: head = [1,2,3]
Output: [1,2,4]
Example 2:

Input: head = [0]
Output: [1]
 

Constraints:

. The number of nodes in the linked list is in the range [1, 100].
. 0 <= Node.val <= 9
. The number represented by the linked list does not contain leading zeros except for the zero itself. 

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
class PlusOne {

    struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /*
        369.Plus-One-Linked-List
        链表题比较适合用递归来做，利用递归返回值来处理当前的节点，很方便。

        本题的一个技巧就是当递归到节点为NULL时，令carry=1。其余的节点就是更新node->val = node->val+carry的处理。
    */
    ListNode* plusOne(ListNode* head) 
    {
        int carry = 0;
        dfs(head, carry);
        if (carry == 0)
            return head;
        else
        {
            ListNode* node = new ListNode(1);
            node->next = head;
            return node;
        }
    }
    
    void dfs(ListNode* head, int& carry) 
    {       
        if (head==NULL)
        {
            carry = 1;
            return;
        }
        
        dfs(head->next, carry);
        
        int val = head->val + carry;
        carry = val / 10;
        head->val = val % 10;        
        
        // if (head->val==3) cout<<val<<endl;
    }


public:
    ListNode* doit_link(ListNode* head) {
        
        ListNode *prev = nullptr, *cur = head;
        while (cur) {
            ListNode* curnext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = curnext;
        }

        ListNode *h = prev, *last = nullptr;
        cur = prev;
        int r = 1;
        while (cur) {
            cur->val += r;
            r = 0;
            if (cur->val >= 10) {
                r = cur->val / 10;
                cur->val %= 10; 
            }
            last = cur;
            cur = cur->next;
        }

        if (r != 0)
            last->next = new ListNode(r);

        cur = prev, prev = nullptr;
        while (cur) {
            ListNode* curnext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = curnext;
        }
        
        return prev;
    }
};