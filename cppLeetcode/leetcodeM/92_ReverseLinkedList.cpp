/*
206. Reverse Linked List

Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
Example 2:

Input: head = [1,2]
Output: [2,1]
Example 3:

Input: head = []
Output: []
 
Constraints:

The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
 
Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
 
*/

#include <functional>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ReverseListI {
    
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

/*
92. Reverse Linked List II

Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 

Example 1:


Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 

Follow up: Could you do it in one pass?

*/



class ReverseListII {

    struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /*
        092.Reverse-Linked-List-II
        本题比较考验对于链表操作的细节。

        我们先遍历到第m-1个和第m个节点。将第m-1个节点记为end_of_start，之后的next要重新指向逆序段的首节点。

        从第m个节点到第n个节点，我们要做链表逆转的操作。基本的思想就是将向后指向的next，变更成向前指向。所以我们每操作一个cur，都要同时准确地知道prev和next。
        处理完之后，prev,cur,next都要正确地移动到下一个位置。最终处理完第n个节点后，此时的cur指向的是第n+1个节点，它就是第三段的首节点start_of_third，同时prev就是第二段的逆序的首节点。我们需要的操作是：

        end_of_first->next = start_of_third;
        start_of_second->next = start_of_third;


        preHead = ListNode(1000)
        pt, preHead.next, i, = preHead, head, 1
        while pt and i < m:
            pt = pt.next
            i += 1

        pStart, pEnd = pt.next, pt
        while pStart and i < n:
            p = pStart.next
            pStart.next = p.next
            p.next = pEnd.next 
            pEnd.next = p
            i += 1

        return preHead.next
    */
    ListNode* reverseBetween(ListNode* head, int m, int n) 
    {
        ListNode* dummy = new ListNode(0, head);
        ListNode* cur = dummy;

        for (int i=1; i<=m-1; i++)
            cur = cur->next;

        ListNode* end_of_fisrt = cur;
        cur = cur->next;

        ListNode *start_of_second = cur;
        ListNode *prev = nullptr, *next = nullptr;
        
        for (int i=m; i<=n; i++){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        end_of_fisrt->next = prev;
        start_of_second->next = cur;
        return dummy->next;
    }


public:
    
    ListNode* doit_link(ListNode* head, int left, int right) {
        
        ListNode h(INT_MAX, head);
        ListNode *cur = head, *last = &h;
        ListNode *pStart = nullptr, *pleft = nullptr;
        
        int cnt = 0;

        while(cur) {
            
            cnt++;

            if (cnt < left) {
                last = cur;
                cur = cur->next;
            } else if (cnt == left) {
                pStart = last;
                pleft = cur;
                cur = cur->next;
                pleft->next = nullptr;
            } else if (cnt == right + 1) {
                pleft->next = cur;
                break;
            } else if (cnt > left) {
                ListNode* next = cur->next;
                cur->next = pStart->next;
                pStart->next = cur;
                cur = next;
            }
        }

        return h.next;
    }
    
    ListNode* reverseBetween(ListNode* head, int m, int n) {

        // Object level variables since we need the changes
        // to persist across recursive calls and Java is pass by value.
        bool stop = false;
        ListNode* left = head;
        stop = false;

        
        std::function<void(ListNode*, int, int)> recurseAndReverse = [&](ListNode* right, int m, int n) {
            // base case. Don't proceed any further
            if (n == 1) {
                return;
            }

            // Keep moving the right pointer one step forward until (n == 1)
            right = right->next;

            // Keep moving left pointer to the right until we reach the proper node
            // from where the reversal is to start.
            if (m > 1) {
                left = left->next;
            }

            // Recurse with m and n reduced.
            recurseAndReverse(right, m - 1, n - 1);

            // In case both the pointers cross each other or become equal, we
            // stop i.e. don't swap data any further. We are done reversing at this
            // point.
            if (left == right || right->next == left) {
                stop = true;            
            }

            // Until the boolean stop is false, swap data between the two pointers
            if (!stop) {
                int t = left->val;
                left->val = right->val;
                right->val = t;

                // Move left one step to the right.
                // The right pointer moves one step back via backtracking.
                left = left->next;
            }
        };

        recurseAndReverse(head, m, n);
        return head;
    }
};