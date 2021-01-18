"""
328. Odd Even Linked List

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
 

Constraints:

The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...
The length of the linked list is between [0, 10^4].

"""


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class OddEvenList:

    def doit_(self, head: 'ListNode') -> 'ListNode':

        even, odd = ListNode(), ListNode()
        cureven, curodd= even, odd
        cur = head

        i = 1
        while cur:
            
            if i % 2 == 1:
                curodd.next, cur = cur, cur.next
                curodd = curodd.next
            else:
                cureven.next, cur = cur, cur.next
                cureven = cureven.next
                
            i += 1

        curodd.next = even.next
        cureven.next = None
        return odd.next

    def doit_(self, head: 'ListNode') -> 'ListNode':

        i = 1
        cur = head
        odd = None
        while cur:

            if i % 2 == 1:
                if not odd:
                    odd = cur

                elif cur.next:
                    node = cur.next
                    cur.next = cur.next.next
                    odd.next, node.next = node, odd.next
                    odd = odd.next

                cur = cur.next
            i += 1

        return head