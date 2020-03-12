/*
 
 
 # 25. Reverse Nodes in k-Group

 # Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

 # k is a positive integer and is less than or equal to the length of the linked list.
 # If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

 # Example:

 # Given this linked list: 1->2->3->4->5

 # For k = 2, you should return: 2->1->4->3->5

 # For k = 3, you should return: 3->2->1->4->5

 # Note:

 # Only constant extra memory is allowed.
 # You may not alter the values in the list's nodes, only nodes itself may be changed.

 
 */

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *prev;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ReverseKGroup {
public:
    ListNode* doit(ListNode* head, int k) {
       
        ListNode ans(0);
        ListNode *h = &ans;
        
        while (head) {
            
            int i = 0;
            ListNode *tmp = head;
            while (tmp && i < k) {
                tmp = tmp->next;
                i++;
            }
            
            if (i == k) {
                ListNode * p = head;
                while (i > 0) {
                    ListNode *n = p->next;
                    p->next = h->next;
                    h->next = p;
                    p = n;
                    i--;
                }
                h = head;
                head = tmp;
                
            } else {
                h->next = head;
                break;
            }
        }
        return ans.next;
    }
};