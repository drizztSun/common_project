"""
92. Reverse Linked List II


Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

"""


class ReverseBetween:

    """
    Approach 1: Recursion
    Intuition

    The idea for linked list reversal using recursion springs from a similar idea that we use for reversing an array. If we want to reverse an array, the huge advantage that we have is the availability of indexes. 
    So, what we can do there is to simply have two pointers, one at the beginning of the array and one at the end. We repeatedly swap elements pointed to by these two pointers and we move both the pointers towards the center of the array. 
    Let's quickly look at this simple algorithm on a sample array before we move on to linked lists.

    Algorithm

    We define a recursion function that will do the job of reversing a portion of the linked list.
    Let's call this function recurse. The function takes in 3 parameters: m being the starting point of the reversal, n being the ending point for the reversal, and a pointer right which will start at the n^{th}n 
    th
    node in the linked list and move backwards with the backtracking of the recursion. If this is not clear at the moment, the diagrams that follow will help.
    Additionally, we have a pointer called left which starts from the m^{th}m 
    th
    node in the linked list and moves forward. In Python, we have to take a global variable for this which get's changed with recursion. In other languages, where changes made in function calls persist, we can consider this pointer as an additional variable for the function recurse.
    In a recursion call, given m, n, and right, we check if n == 1. If this is the case, we don't need to go any further.
    Until we reach n = 1, we keep moving the right pointer one step forward and after doing that, we make a recursive call with the value of n decreased by 1. At the same time, we keep on moving the left pointer forward until m == 1. When we refer to a pointer being moved forward, it essentially means pointer.next.
    So we backtrack as soon as n reaches 1. At that point of time, the right pointer is at the last node of the sublist we want to reverse and the left has already reached the first node of this sublist. So, we swap out the data and move the left pointer one step forward using left = left.next. We need this change to persist across the backtracking process.
    From there on, every time we backtrack, the right pointer moves one step backwards. This is the simulation we've been mentioning all along. The backward movement is simulated by backtracking.
    We stop the swaps when either right == left, which happens if the sublist size is odd, or, right.next == left which happens when during the backtracking process for an even sized sublist, the right pointer crosses left. We use a global boolean flag for stopping the swaps once these conditions are met.
    Let's look at a series of diagrams explaining the process on a sample linked list. Hopefully, things would be clearer after this.

    Complexity Analysis

    Time Complexity: O(N) considering the list consists of NN nodes. We process each of the nodes at most once (we don't process the nodes after the n node from the beginning.
    Space Complexity: O(1) since we simply adjust some pointers in the original linked list and only use O(1)O(1) additional memory for achieving the final result.

    """
    def doit_(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """

        # Empty list
        if not head:
            return None

        # Move the two pointers until they reach the proper starting point
        # in the list.
        cur, prev = head, None
        while m > 1:
            prev = cur
            cur = cur.next
            m, n = m - 1, n - 1

        # The two pointers that will fix the final connections.
        tail, con = cur, prev

        # Iteratively reverse the nodes until n becomes 0.
        # don't use cur, cur.next, prev = cur.next, prev, cur, it has variable assignment issues.
        while n:
            third = cur.next
            cur.next = prev
            prev = cur
            cur = third
            n -= 1

        # Adjust the final connections as explained in the algorithm
        if con:
            con.next = prev
        else:
            head = prev
        tail.next = cur
        return head

    def doit_(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        preHead = ListNode(1000)
        pt, preHead.next, i, = preHead, head, 1
        while pt and i < m:
            pt = pt.next
            i += 1

        pStart, pEnd = pt.next, pt
        while pStart and i < n:
            p = pStart.next
            pStart.next = p.next
            p.next = pEnd.next 
            pEnd.next = p
            i += 1

        return preHead.next