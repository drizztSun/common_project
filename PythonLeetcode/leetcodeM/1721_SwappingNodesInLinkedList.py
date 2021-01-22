"""
1721. Swapping Nodes in a Linked List


You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Example 2:

Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
Example 3:

Input: head = [1], k = 1
Output: [1]
Example 4:

Input: head = [1,2], k = 1
Output: [2,1]
Example 5:

Input: head = [1,2,3], k = 2
Output: [1,2,3]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 10^5
0 <= Node.val <= 100
"""


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class SwapNodes:


    def doit_(self, head: ListNode, k: int) -> ListNode:
        
        N, cur = 0, head
        while cur:
            cur = cur.next
            N += 1
        
        slow = head
        for _ in range(k-1):
            slow = slow.next
        
        fast = head
        for _ in range(N-k):
            fast = fast.next
            
        slow.val, fast.val = fast.val, slow.val
        return head

    def doit_(self, head: ListNode, k: int) -> ListNode:
        N, cur, slow = 0, head, None
        while cur:
            if N == k-1:
                slow = cur
            cur = cur.next
            N += 1
        
        fast = head
        for i in range(N-k):
            fast = fast.next
        
        print(slow.val, fast.val)
        slow.val, fast.val = fast.val, slow.val
        return head

    def doit_(self, head: ListNode, k: int) -> ListNode:
        cur, front, end = head, None, None
        length = 0
        
        while cur:
            length += 1
            if end:
                end = end.next
            
            if length == k:
                front = cur
                end = head
            
            cur = cur.next
            
        front.val, end.val = end.val, front.val
        return head


    def doit_(self, head: list, k: int) -> list:
        
        N, cur = 0, head
        while cur:
            cur = cur.next
            N += 1
            
        distance = abs(N - 2 * k) + 1
        
        if k == N // 2 + 1 and N % 2 == 1:
            return head

        if k > N//2:
            k = N - k

        step, slow, fast = 0, head, head
        while step < k:
            fast = fast.next
            if step >= distance:
                slow = slow.next
            step += 1
        
        slownext, fastnext = slow.next, fast.next
        print(slownext.val, fastnext.val)
        
        slow.next, fast.next = slownext.next, fastnext.next
        slow.next, fastnext.next = fastnext, slow.next
        fast.next, slownext.next = slownext, fast.next
        
        return head
        
        
if __name__ == '__main__':

    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))

    SwapNodes().doit_(head, 2)