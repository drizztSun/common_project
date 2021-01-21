"""
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

"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class RotateRight:
    
    def doit_search(self, head: list, k: int) -> list:
        
        if not head: return head
        
        length = 0
        node = head
        while node:
            length += 1
            node = node.next
            
        k %= length
        
        if k == 0: return head
        
        slow, fast = head, head
        i = 0
        while fast.next:
            i += 1
            fast = fast.next
            if i > k:
                slow = slow.next
                
        tmp = head
        
        head, fast.next, slow.next = slow.next, tmp, None
        
        return head

    """
        Approach 1:
        Intuition

        The nodes in the list are already linked, and hence the rotation basically means

        To close the linked list into the ring.

        To break the ring after the new tail and just in front of the new head.

        rotate

        Where is the new head?

        In the position n - k, where n is a number of nodes in the list. The new tail is just before, in the position n - k - 1.

        We were assuming that k < n. What about the case of k >= n?

        k could be rewritten as a sum k = (k // n) * n + k % n, where the first term doesn't result in any rotation. Hence one could simply replace k by k % n to always have number of rotation places smaller than n.

        Algorithm

        The algorithm is quite straightforward :

        Find the old tail and connect it with the head old_tail.next = head to close the ring. Compute the length of the list n at the same time.

        Find the new tail, which is (n - k % n - 1)th node from the head and the new head, which is (n - k % n)th node.

        Break the ring new_tail.next = None and return new_head.

        Implementation

        Complexity Analysis

        Time complexity : \mathcal{O}(N)O(N) where NN is a number of elements in the list.

        Space complexity : \mathcal{O}(1)O(1) since it's a constant space solution.

    """
    def rotateRight(self, head: 'ListNode', k: 'int') -> 'ListNode':
        # base cases
        if not head:
            return None
        if not head.next:
            return head
        
        # close the linked list into the ring
        old_tail = head
        n = 1
        while old_tail.next:
            old_tail = old_tail.next
            n += 1
        old_tail.next = head
        
        # find new tail : (n - k % n - 1)th node
        # and new head : (n - k % n)th node
        new_tail = head
        for i in range(n - k % n - 1):
            new_tail = new_tail.next
        new_head = new_tail.next
        
        # break the ring
        new_tail.next = None
        
        return new_head