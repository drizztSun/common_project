/*
 
 21. Merge Two Sorted Lists
 
 
 Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

 Example:

 Input: 1->2->4, 1->3->4
 Output: 1->1->2->3->4->4
 
 
 */



//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
 

class MergeTwoLists {
    
public:
    ListNode* doit(ListNode* l1, ListNode* l2) {
        
        ListNode ans(-1);
        ListNode *h = &ans;
        
        while (l1 || l2) {
            
            ListNode *tmp = nullptr;
            if (!l2 || (l1 && l2 && l1->val <= l2->val)) {
                tmp = l1;
                l1 = l1->next;
            } else if (!l1 || (l1 && l2 && l1->val > l2->val)) {
                tmp = l2;
                l2 = l2->next;
            }
            
            h->next = tmp;
            h = tmp;
            h->next = nullptr;
        }
        
        return ans.next;
    }
};

void test_21_merge_two_sorted_list() {
    
}
