class Solution:


    def reverse_link(cur, n):

        while n:
            third = cur.next
            cur.next = prev
            prev = cur
            cur = third
            n -= 1

