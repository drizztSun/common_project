
class LinkNode:

    def __init__(self, val, next=None):
        self.val = val
        self.next = next


class Solution:

    def reverse_link(cur, n):

        while n:
            third = cur.next
            cur.next = prev
            prev = cur
            cur = third
            n -= 1

    def partition_link(head, x):
        
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