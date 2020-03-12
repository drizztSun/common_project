
/*
 
 
 206. Reverse Linked List
 
 
 Reverse a singly linked list.

 Example:

 Input: 1->2->3->4->5->NULL
 Output: 5->4->3->2->1->NULL
 Follow up:
 
 */


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ReverseList {
    
public:
    ListNode* doit(ListNode* head) {

        ListNode* ans = nullptr;
        
        while (head) {
            ListNode* next = head->next;
            if (!ans) {
                head->next = nullptr;
                ans = head;
            } else {
                head->next = ans;
                ans = head;
            }
            head = next;
        }
        return ans;
    }
};
