# 876. Middle of the Linked List

# Given a non-empty, singly linked list with head node head, return a middle node of linked list.

# If there are two middle nodes, return the second middle node.


# Example 1:

# Input: [1,2,3,4,5]
# Output: Node 3 from this list (Serialization: [3,4,5])
# The returned node has value 3.  (The judge's serialization of this node is [3,4,5]).
# Note that we returned a ListNode object ans, such that:
# ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, and ans.next.next.next = NULL.

# Example 2:

# Input: [1,2,3,4,5,6]
# Output: Node 4 from this list (Serialization: [4,5,6])
# Since the list has two middle nodes with values 3 and 4, we return the second one.


# Note:

# The number of nodes in the given list will be between 1 and 100.


# Example 1:

# Input: [1,2,3,4,5]
# Output: Node 3 from this list (Serialization: [3,4,5])
# The returned node has value 3.  (The judge's serialization of this node is [3,4,5]).
# Note that we returned a ListNode object ans, such that:
# ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, and ans.next.next.next = NULL.


# Example 2:

# Input: [1,2,3,4,5,6]
# Output: Node 4 from this list (Serialization: [4,5,6])
# Since the list has two middle nodes with values 3 and 4, we return the second one.


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class MiddleNode:

    def doit(self, head):
        if not head:
            return head

        slow, fast = head, head.next

        while fast:

            fast = fast.next
            if not fast:
                return slow.next

            fast = fast.next
            slow = slow.next

        else:
            return slow

    def doit(self, head):
        list_1 = []
        while head:
            list_1.append(head)
            head = head.next

        y = int(len(list_1)/2)
        # print(y)
        return list_1[y]


if __name__ == '__main__':

    r = ListNode(1)
    r.next = ListNode(2)
    r.next.next = ListNode(3)
    r.next.next.next = ListNode(4)

    res = MiddleNode().doit(r)

    r.next.next.next.next = ListNode(5)

    res = MiddleNode().doit(r)

    r.next.next.next.next.next = ListNode(6)

    res = MiddleNode().doit(r)

    pass
