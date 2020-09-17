"""
23. Merge k Sorted Lists

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.



Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []

"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None


class MergeKLists(object):

    def doit_heap(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        from heapq import *

        buff = [(i.val, i) for i in a if i]
        heapify(buff)
        tail = ListNode()
        head = tail
        while buff:
            n = heappop(buff)
            tail.next = n[1]
            if n[1].next != None:
                heappush(buff, (n[1].next.val, n[1].next))
            tail = tail.next
        return head.next

    def doit_binary_search(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        import bisect
        st, res = [], ListNode(100)

        for i, a in enumerate(lists):
            if a:
                bisect.insort(st, (-a.val, i, a))

        node = res
        while st:
            v, i, A = st.pop()
            node.next = A
            A = A.next

            if A:
                bisect.insort(st, (-A.val, i, A))
            
            node = node.next

        return res.next

    def doit(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        import heapq
        st, res = [], ListNode(100)
        for i, a in enumerate(lists):
            if a:
                heapq.heappush(st, (a.val, i, a))

        node = res
        while st:
            v, i, A = heapq.heappop(st)
            node.next = A
            A = A.next

            if A:
                heapq.heappush(st, (A.val, i, A))

            node = node.next

        return res.next         

    def doit(self, lists):
    
        if len(lists) == 0:
            return None
        result = []
        for i in range (len(lists)):
            while lists[i] != None:
                result.append(lists[i].val)
                lists[i] = lists[i].next
        result.sort()
        ret = None
        for i in reversed( range (len(result))):
            tmp = ListNode(result[i])
            tmp.next = ret
            ret = tmp
        return ret   

    def doit_divide_and_conquer(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        def merge2Lists(l1, l2):
            head = point = ListNode(0)
            while l1 and l2:
                if l1.val <= l2.val:
                    point.next = l1
                    l1 = l1.next
                else:
                    point.next = l2
                    l2 = l1
                    l1 = point.next.next
                point = point.next
            if not l1:
                point.next=l2
            else:
                point.next=l1
            return head.next

        amount = len(lists)
        interval = 1
        while interval < amount:
            for i in range(0, amount - interval, interval * 2):
                lists[i] = merge2Lists(lists[i], lists[i + interval])
            interval *= 2
        return lists[0] if amount > 0 else lists




if __name__ == "__main__":

    arr = []
    arr.append(ListNode(1))
    arr[-1].next = ListNode(4)
    arr[-1].next.next = ListNode(5)

    arr.append(ListNode(1))
    arr[-1].next = ListNode(3)
    arr[-1].next.next = ListNode(4)

    arr.append(ListNode(2))
    arr[-1].next = ListNode(6)           

    res = MergeKLists().doit(arr)