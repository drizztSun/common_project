# 25. Reverse Nodes in k-Group

# Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

# k is a positive integer and is less than or equal to the length of the linked list.
# If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

# Example:

# Given this linked list: 1->2->3->4->5

# For k = 2, you should return: 2->1->4->3->5

# For k = 3, you should return: 3->2->1->4->5

# Note:

# Only constant extra memory is allowed.
# You may not alter the values in the list's nodes, only nodes itself may be changed.


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class ReverseKGroup:
    def doit(self, head, k):

        res = ListNode(100)
        h = res

        while head:

            i = 0
            tmp = head

            while i < k and tmp:
                tmp = tmp.next
                i += 1

            if i == k:
                s = head
                while i > 0:
                    n = s.next
                    s.next, h.next = h.next, s
                    s = n
                    i -= 1
                h = head
                head = s
            else:
                h.next = head
                break

        return res.next

    def doit1(self, head, k):
        if k == 1:
            return head

        cnt = 0
        p = head
        while p:
            cnt += 1
            p = p.next

        ans = ListNode(0)
        last = ans
        last.next = head

        for _ in range(cnt // k):
            first = last.next
            prev, p = first, first.next
            for _ in range(k - 1):
                nxt = p.next
                p.next = prev
                prev = p
                p = nxt
            last.next = prev
            first.next = p
            last = first
        return ans.next

    def doitxxx(self, head, k):

        root = None
        while head:
            h, e = None, None
            for i in range(k):
                if not head:
                    break
                next = head.next
                if not h and not e:
                    h = e = head
                    e.next = None
                else:
                    head.next = h
                    h.next = head
                head = next

            if h and e:
                e.next = root
                root = h

        return root


if __name__ == "__main__":

    n5 = ListNode(5)
    n4 = ListNode(4)
    n3 = ListNode(3)
    n2 = ListNode(2)
    root = ListNode(1)

    root.next = n2
    n2.next = n3
    n3.next = n4
    n4.next = n5

    res = ReverseKGroup().doit(root, 2)

    n5 = ListNode(5)
    n4 = ListNode(4)
    n4.next = n5
    n3 = ListNode(3)
    n3.next = n4
    n2 = ListNode(2)
    n2.next = n3
    root = ListNode(1)
    root.next = n2

    res = ReverseKGroup().doit(root, 3)

    pass
