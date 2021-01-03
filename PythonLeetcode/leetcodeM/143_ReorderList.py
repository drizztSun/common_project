"""
143. Reorder List

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class ReorderList:

    def doit_stack(self, head: list) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
        if not head:
            return None
        array = []

        while head:
            array.append(head)
            head = head.next

        for i in range(len(array)):
            array[i].next = array[-i - 1]

            if i + 1 < len(array) - 1 - i:
                array[-i - 1].next = array[i + 1]
            else:
                array[-i - 1].next = None
                break

        return array[0]


    """
    Solution Bricks
    This problem is a combination of these three easy problems:
    
    Middle of the Linked List.
    
    Reverse Linked List.
    
    Merge Two Sorted Lists.
    
    
    Approach 1: Reverse the Second Part of the List and Merge Two Sorted Lists
    Overview
    
    Find a middle node of the linked list. If there are two middle nodes, return the second middle node. Example: for the list 1->2->3->4->5->6, the middle element is 4.
    
    Once a middle node has been found, reverse the second part of the list. Example: convert 1->2->3->4->5->6 into 1->2->3->4 and 6->5->4.
    
    Now merge the two sorted lists. Example: merge 1->2->3->4 and 6->5->4 into 1->6->2->5->3->4.
    
    Now let's check each algorithm part in more detail.

    Find a Middle Node
    
    Let's use two pointers, slow and fast. While the slow pointer moves one step forward slow = slow.next, the fast pointer moves two steps forward fast = fast.next.next, i.e. fast traverses twice as fast as slow. 
    When the fast pointer reaches the end of the list, the slow pointer should be in the middle.

    
    """
    def doit_link(self, head: list) -> None:
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