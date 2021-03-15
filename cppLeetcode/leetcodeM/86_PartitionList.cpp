/*
86. Partition List

Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

 

Example 1:


Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Example 2:

Input: head = [2,1], x = 2
Output: [1,2]
 

Constraints:

The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200

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

public:

    struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* partition(ListNode* head, int x) {
        
        ListNode h(INT_MAX, head);
        ListNode *left = &h, *it = head, *last = &h;

        while (it) {

            if (it->val < x) {

                ListNode* curnext = it->next;

                if (it != left->next) {
                    ListNode* leftnext = left->next;
                    it->next = leftnext;
                    left->next = it;
                    last->next = curnext;
                }
                left = left->next;
                it = curnext;
                continue;
            }

            last = it;
            it = it->next;
        }

        return h.next;
    }
    
    ListNode* doit_link(ListNode* head, int x) {

        // before and after are the two pointers used to create the two list
        // before_head and after_head are used to save the heads of the two lists.
        // All of these are initialized with the dummy nodes created.
        ListNode *before_head = new ListNode(0);
        ListNode *before = before_head;
        ListNode *after_head = new ListNode(0);
        ListNode *after = after_head;

        while (head != nullptr) {

            // If the original list node is lesser than the given x,
            // assign it to the before list.
            if (head->val < x) {
                before->next = head;
                before = before->next;
            } else {
                // If the original list node is greater or equal to the given x,
                // assign it to the after list.
                after->next = head;
                after = after->next;
            }

            // move ahead in the original list
            head = head->next;
        }

        // Last node of "after" list would also be ending node of the reformed list
        after->next = nullptr;

        // Once all the nodes are correctly assigned to the two lists,
        // combine them to form a single list which would be returned.
        before->next = after_head->next;

        return before_head->next;
    }
};