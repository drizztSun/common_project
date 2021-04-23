/*
141. Linked List Cycle

Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. 
Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
Example 2:


Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
Example 3:


Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?


142. Linked List Cycle II


Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. 
Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Notice that you should not modify the linked list.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
Example 2:


Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
Example 3:


Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?

*/


class DetectCycle {

    struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /*
        141. Linked List Cycle
        算法：快慢指针。  
        使用快慢指针的典型用途。成环的链表一定会让快指针追上慢指针.
    */
    bool hasCycle(ListNode *head) 
    {
        if (head == nullptr) return false;
        
        ListNode* slow=head;
        ListNode* fast=head;
        
        while (fast->next!=nullptr && fast->next->next!=nullptr)
        {
            fast=fast->next->next;
            slow=slow->next;
            
            if (fast==slow) return true;
        }
        
        return false;
        
    }

    bool hasCycle(ListNode *head) {
        
        if (!head) return false;
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        do {
            
            if (!slow) break;
            slow = slow->next;
            
            if (!fast || !fast->next) return false;
            fast = fast->next->next;
            
        } while (slow != fast);
        
        return slow == fast;        
    }
    
    /*
        142. Linked List Cycle II
        算法思想：快慢指针、链表
        从第141题已知，用快慢指针的方法可以判断是否链表存在环。

        假设两个指针相遇时，快指针走过了m步进入环的入口然后转了k1圈（每圈n步）又多p步；同理，慢指针走过了m步进入环的入口然后转了k2圈又多p步。由于两者是两倍关系，所以 m+k1*n+p = 2*(m+k2*n+p)。

        化简之后得到 m = (k1-2k2)*n-p，变换一下 p+m = (k1-2k2)*n

        因为慢指针目前已经比整数圈多走了p步，结合这个数学式子，这说明如果慢指针再走m步的话，又会凑成整数圈，即到了环的入口。怎么确定m呢？只要另开一个指针从head开始与慢指针一齐走，它们相遇的地方就是环的入口。

        本题的算法还有一个非常巧妙的应用：287. Find the Duplicate Number
    */
    ListNode *detectCycle(ListNode *head) 
    {
        if (head==NULL) return NULL;
        
        ListNode* slow=head;
        ListNode* fast=head;
        int flag=0;
        
        while (fast->next!=NULL && fast->next->next!=NULL)
        {
            fast=fast->next->next;
            slow=slow->next;
            
            if (fast==slow) 
            {
                flag=1;
                break;
            }
        }
        
        if (flag==0) return NULL;
        
        fast=head;
        while (fast!=slow)
        {
            fast=fast->next;
            slow=slow->next;
        }
        
        return fast;
        
    }


public:

    bool hasCycle(ListNode *head) {
        
        if (!head) return false;
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        do {
            
            if (!slow) break;

            slow = slow->next;
            
            if (!fast || !fast->next) return false;
            
            fast = fast->next->next;
            
        } while (slow != fast);
        
        return slow == fast;        
    }

    ListNode* doit_link(ListNode *head) {
       
        if (!head) return nullptr;
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        
        do {
            
            if (!slow) break;

            slow = slow->next;
            
            if (!fast || !fast->next) return nullptr;
            
            fast = fast->next->next;
            
        } while (slow != fast);
        
        if (slow != fast) return nullptr;
        
        slow = head;
        
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;
    }
};