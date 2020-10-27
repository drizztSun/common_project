"""
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

You may not modify the values in the list's nodes. Only nodes itself may be changed.



Example 1:


Input: head = [1,2,3,4]
Output: [2,1,4,3]
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [1]
Output: [1]
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class SwapPairs(object):

    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        result, a = ListNode(1000), head
        tail = result

        while a != None:
            c = None
            if a.next != None:
                tail.next = a.next
                c = a.next.next
                a.next.next = a
                a.next = None

                tail = tail.next.next
            else:
                tail.next = a
            a = c

        result = result.next

        return result


    """
    Approach 2: Iterative Approach
    Intuition
    
    The concept here is similar to the recursive approach. We break the linked list into pairs by jumping in steps of two. 
    The only difference is, unlike recursion, we swap the nodes on the go. After swapping a pair of nodes, say A and B, we need to link the node B to the node that was right before A. To establish this linkage we save the previous node of node A in prevNode.
    """
    def doit(self, head: ListNode) -> ListNode:
        """
        :type head: ListNode
        :rtype: ListNode
        """
        # Dummy node acts as the prevNode for the head node
        # of the list and hence stores pointer to the head node.
        dummy = ListNode(-1)
        dummy.next = head

        prev_node = dummy

        while head and head.next:

            # Nodes to be swapped
            first_node = head;
            second_node = head.next;

            # Swapping
            prev_node.next = second_node
            first_node.next = second_node.next
            second_node.next = first_node

            # Reinitializing the head and prev_node for next swap
            prev_node = first_node
            head = first_node.next

        # Return the new head node.
        return dummy.next