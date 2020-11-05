"""
86. Partition List


Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:

Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5

"""


class Partition(object):

    def doit_list_1(self, head, x):
        """
        :type head: ListNode
        :type x: int
        :rtype: ListNode
        """
        result = ListNode(0)
        result.next = head
        st, it, last = result, head, result

        while it:
            if it.val < x:
                next = it.next
                if it != st.next:
                    st.next, it.next, last.next = it, st.next, next
                it, st = next, st.next
                continue

            last = it
            it = it.next

        return result.next

    def doit_list(self, head, x):
        """
        :type head: ListNode
        :type x: int
        :rtype: ListNode
        """
        right = head
        h = ListNode()
        h.next, left = head, h

        while right and right.val < x:
            left = right
            right = right.next

        if not right:
            return h.next

        last = left
        while right:

            if right.val < x:
                c = right
                last.next = right.next
                right = right.next

                left.next, c.next = c, left.next
                left = left.next
            else:
                last = right
                right = right.next

        return h.next