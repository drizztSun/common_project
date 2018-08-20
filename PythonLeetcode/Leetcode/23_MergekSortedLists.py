# 23. Merge k Sorted Lists

# Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

# Example:

# Input:
# [
#  1->4->5,
#  1->3->4,
#  2->6
# ]
# Output: 1->1->2->3->4->4->5->6


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None




class MergeKLists(object):


    def doit1(self, lists):
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

    pass
    