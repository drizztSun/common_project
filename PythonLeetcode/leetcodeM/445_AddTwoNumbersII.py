"""

445. Add Two Numbers II


You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class AddTwoNumbers(object):

    def doit(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        l1Stack, l2Stack = [], []
        while l1:
            l1Stack.append(l1.val)
            l1 = l1.next
        while l2:
            l2Stack.append(l2.val)
            l2 = l2.next

        prev, head, accum = None, None, 0
        while l1Stack or l2Stack:
            a, b = 0, 0
            if l1Stack:
                a = l1Stack.pop()
            if l2Stack:
                b = l2Stack.pop()

            val = (a + b + accum) % 10
            accum = (a + b + accum) / 10

            head = ListNode(val)
            head.next = prev
            prev = head

        if accum == 1:
            head = ListNode(accum)
            head.next = prev

        return head

    def doit_reverse(self, l1: ListNode, l2: ListNode) -> ListNode:

        def reverseList(head: ListNode) -> ListNode:
            last = None
            while head:
                # keep the next node
                tmp = head.next
                # reverse the link
                head.next = last
                # update the last node and the current node
                last = head
                head = tmp

            return last

        # reverse lists
        l1 = reverseList(l1)
        l2 = reverseList(l2)

        head = None
        carry = 0
        while l1 or l2:
            # get the current values
            x1 = l1.val if l1 else 0
            x2 = l2.val if l2 else 0

            # current sum and carry
            val = (carry + x1 + x2) % 10
            carry = (carry + x1 + x2) // 10

            # update the result: add to front
            curr = ListNode(val)
            curr.next = head
            head = curr

            # move to the next elements in the lists
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None

        if carry:
            curr = ListNode(carry)
            curr.next = head
            head = curr

        return head

    def doit_(self, l1: ListNode, l2: ListNode) -> ListNode:

        # find the length of both lists
        n1 = n2 = 0
        curr1, curr2 = l1, l2
        while curr1:
            curr1 = curr1.next
            n1 += 1
        while curr2:
            curr2 = curr2.next
            n2 += 1

        # parse both lists
        # and sum the corresponding positions
        # without taking carry into account
        # 3->3->3 + 7->7 --> 3->10->10 --> 10->10->3
        curr1, curr2 = l1, l2
        head = None
        while n1 > 0 and n2 > 0:
            val = 0
            if n1 >= n2:
                val += curr1.val
                curr1 = curr1.next
                n1 -= 1
            if n1 < n2:
                val += curr2.val
                curr2 = curr2.next
                n2 -= 1

            # update the result: add to front
            curr = ListNode(val)
            curr.next = head
            head = curr

        # take the carry into account
        # to have all elements to be less than 10
        # 10->10->3 --> 0->1->4 --> 4->1->0
        curr1, head = head, None
        carry = 0
        while curr1:
            # current sum and carry
            val = (curr1.val + carry) % 10
            carry = (curr1.val + carry) // 10

            # update the result: add to front
            curr = ListNode(val)
            curr.next = head
            head = curr

            # move to the next elements in the list
            curr1 = curr1.next

        # add the last carry
        if carry:
            curr = ListNode(carry)
            curr.next = head
            head = curr

        return head

    def doit(self, l1: ListNode, l2: ListNode) -> ListNode:

        n1, cur1, n2, cur2 = 0, l1, 0, l2
        while cur1:
            n1 += 1
            cur1 = cur1.next

        while cur2:
            n2 += 1
            cur2 = cur2.next

        head = None
        cur1, cur2 = l1, l2
        while n1 > 0 and n2 > 0:
            val = 0
            if n1 >= n2:
                val = cur1.val
                cur1 = cur1.next
                n1 -= 1

            if n2 > n1:
                val += cur2.val
                cur2 = cur2.next
                n2 -= 1

            cur = ListNode(val)
            cur.next = head
            head = cur

        carry = 0
        curr1, head = head, ListNode()

        while curr1:
            carry, curr1.val = divmod(curr1.val + carry, 10)

            next = curr1.next
            head.next, curr1.next = curr1, head.next
            curr1 = next

        if carry:
            c = ListNode(1)
            head.next, c.next = c, head.next

        return head.next


