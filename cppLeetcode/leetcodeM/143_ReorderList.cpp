/*
143. Reorder List

You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4]
Output: [1,4,2,3]
Example 2:


Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
 

Constraints:

The number of nodes in the list is in the range [1, 5 * 104].
1 <= Node.val <= 1000

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
class ReorderList {


    struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /*
        143.Reorder-List.cpp
        此题不难，但是比较繁琐，需要耐心理清思路，细致地操作指针。

        其中对于一段链表进行逆序操作的基本算法是：不断从源链表首摘下一个节点（同时指针后移），拼接到目标链表首（同时指针前移）。

        得到两段链表之后，交替摘取节点拼接到新链表上。
    */
    void reorderList(ListNode* head) 
    {
        if (head==NULL || head->next==NULL)
            return;
        
        ListNode* h=new ListNode(0);
        h->next=head;
        
        ListNode* p=h;
        int count=0;
        while (p->next!=NULL)
        {
            p=p->next;
            count++;
        }        
        p=h;
        for (int i=0; i<(count-count/2); i++)
            p=p->next;       
                                      
        ListNode* temp=p->next;
        p->next=NULL;
        p=temp;
        ListNode* q=NULL;
        while (p!=NULL)
        {
            ListNode* temp=p->next;
            p->next=q;
            q=p;
            p=temp;
        }
        
        p=head;        
        while (p!=NULL || q!=NULL)
        {
            if (p!=NULL)
            {
                h->next=p;
                h=h->next;
                p=p->next;
            }
            if (q!=NULL)
            {
                h->next=q;
                h=h->next;
                q=q->next;
            }
        }        
    }

public:

    /*
        if not head:
            return 
        
        # find the middle of linked list [Problem 876]
        # in 1->2->3->4->5->6 find 4 
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next 
            
        # reverse the second part of the list [Problem 206]
        # convert 1->2->3->4->5->6 into 1->2->3->4 and 6->5->4
        # reverse the second half in-place
        prev, curr = None, slow
        while curr:
            curr.next, prev, curr = prev, curr, curr.next       

        # merge two sorted linked lists [Problem 21]
        # merge 1->2->3->4 and 6->5->4 into 1->6->2->5->3->4
        first, second = head, prev
        while second.next:
            first.next, first = second, first.next
            second.next, second = first, second.next
    
    */

    void doit_link(ListNode* head) {

        if (!head) return;

        // find the middle of linked list [Problem 876]
        // in 1->2->3->4->5->6 find 4 
        ListNode *slow = head, *fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // reverse the second part of the list [Problem 206]
        // convert 1->2->3->4->5->6 into 1->2->3->4 and 6->5->4
        // reverse the second half in-place
        ListNode *prev = nullptr, *cur = slow;
        while (cur) {
            ListNode* curnext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = curnext;
        }

        // merge two sorted linked lists [Problem 21]
        // merge 1->2->3->4 and 6->5->4 into 1->6->2->5->3->4
        ListNode *first = head, *second = prev;
        while (second->next) {
            ListNode *firstnext = first->next;
            ListNode *secondnext = second->next;

            first->next = second;
            second->next = firstnext;

            first = firstnext;
            second = secondnext;
        }
    }
};