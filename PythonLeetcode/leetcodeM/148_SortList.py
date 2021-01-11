"""
148. Sort List


Given the head of a linked list, return the list after sorting it in ascending order.

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

 

Example 1:


Input: head = [4,2,1,3]
Output: [1,2,3,4]
Example 2:


Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Example 3:

Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-10^5 <= Node.val <= 10^5
"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

"""
Overview
The problem is to sort the linked list in \mathcal{O}(n \log n)O(nlogn) time and using only constant extra space. 
If we look at various sorting algorithms, Merge Sort is one of the efficient sorting algorithms that is popularly used for sorting the linked list. 
The merge sort algorithm runs in \mathcal{O}(n \log n)O(nlogn) time in all the cases. Let's discuss approaches to sort linked list using merge sort.

Quicksort is also one of the efficient algorithms with the average time complexity of \mathcal{O}(n \log n)O(nlogn). But the worst-case time complexity is O(n^2). 
Also, variations of the quick sort like randomized quicksort are not efficient for the linked list because unlike arrays, random access in the linked list is not possible in O(1) time. 
If we sort the linked list using quicksort, we would end up using the head as a pivot element which may not be efficient in all scenarios.

"""

class SortList:

    def doit_search(self, head: list) -> list:
        """
        :type head: ListNode
        :rtype: ListNode
        """
        def merge(l1, l2):
            result = ListNode(100)
            p = result

            while l1 and l2:
                if l1.val < l2.val:
                    p.next = l1
                    l1 = l1.next
                else:
                    p.next = l2
                    l2 = l2.next
                p = p.next

            if l1:
                p.next = l1

            if l2:
                p.next = l2
            
            return result.next
        
        def mergeSort(head):
            if head == None or head.next == None:
                return head
                
            slow, fast, prev = head, head, None
            while fast:
                prev = slow
                slow = slow.next
                fast = fast.next
                if fast:
                   fast = fast.next
        
            prev.next = None
            s1 = mergeSort(head)
            s2 = mergeSort(slow)

            return merge(s1, s2)
      
        return mergeSort(head)

    def sortList(self, head: ListNode) -> ListNode:  
        def quicksort(head, tail):
            if head == tail:
                return head          
            def partition(head, tail): 
                temp = ListNode(0)
                temp.next = head 
                pivot = head
                prev = head
                cur = head.next
                while cur != tail: 
                    if cur.val < pivot.val:
                        next = cur.next
                        prev.next = cur.next
                        cur.next = temp.next
                        temp.next = cur
                        cur = next
                    elif cur.val > pivot.val:
                        prev = cur
                        cur = cur.next
                    else:
                        next = cur.next
                        prev.next = cur.next
                        cur.next = pivot.next
                        pivot.next = cur
                        cur = next
                        if prev==pivot:
                            prev = prev.next
                        pivot = pivot.next   
                return temp.next, pivot
            left, pivot = partition(head, tail)
            left = quicksort(left, head)
            pivot.next = quicksort(pivot.next, tail)
            return left
        
        return quicksort(head, None)

        