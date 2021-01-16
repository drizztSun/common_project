"""
1265. Print Immutable Linked List in Reverse


You are given an immutable linked list, print out all values of each node in reverse with the help of the following interface:

ImmutableListNode: An interface of immutable linked list, you are given the head of the list.
You need to use the following functions to access the linked list (you can't access the ImmutableListNode directly):

ImmutableListNode.printValue(): Print value of the current node.
ImmutableListNode.getNext(): Return the next node.
The input is only given to initialize the linked list internally. You must solve this problem without modifying the linked list. In other words, you must operate the linked list using only the mentioned APIs.



Example 1:

Input: head = [1,2,3,4]
Output: [4,3,2,1]
Example 2:

Input: head = [0,-4,-1,3,-5]
Output: [-5,3,-1,-4,0]
Example 3:

Input: head = [-2,0,6,4,4,-6]
Output: [-6,4,4,6,0,-2]


Constraints:

The length of the linked list is between [1, 1000].
The value of each node in the linked list is between [-1000, 1000].


Follow up:

Could you solve this problem in:

Constant space complexity?
Linear time complexity and less than linear space complexity?


"""


# """
# This is the ImmutableListNode's API interface.
# You should not implement it, or speculate about its implementation.
# """
# class ImmutableListNode:
#     def printValue(self) -> None: # print the value of this node.
#     def getNext(self) -> 'ImmutableListNode': # return the next node.

class PrintLinkedListInReverse:

    def doit_stack(self, head: 'ImmutableListNode') -> None:

        st = []
        while head:
            st.append(head)
            head = head.getNext()

        while st:
            st.pop().printValue()

    def doit_(self, head: 'ImmutableListNode') -> None:

        cur = head
        last = None

        while last != head:

            while cur.getNext() != last:
                cur = cur.getNext()

            last = cur
            cur.printValue()
            cur = head

"""
    Welcome to add more combinations of time and space complexity.

    n is length of linked list.
    
    time	space	algorithm
    O(n)	O(n)	recursion or use stack
    O(n)	O(n^(1/t) + t) for an arbitrary positive integer t	sqrt decomposition
    O(n lg n)	O(lg n)	divide and conquer
    O(n^2)	O(1)	load a magazine?
        

"""


class Solution:
    """
        recursion or use stack
    """
    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:
        if head:
            self.printLinkedListInReverse(head.getNext())
            head.printValue()

    """
        sqrt decomposition
        Divide the linked list into n^(1/2) blocks of size n^(1/2);
        Then the start-nodes of these blocks are stored in a stack of length n^(1/2).
        Finally, take blocks from the stack and print it recursively with time O(n^(1/2)) and space O(n^(1/2)).
        The total time complexity is O(n) and space O(n^(1/2)).
    """
    def printLinkedListInReverseDirect(self, head, size):
        if size and head:
            self.printLinkedListInReverseDirect(head.getNext(), size - 1)
            head.printValue()

    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:
        def getLinkedListSize(head):
            size = 0
            while head != None:
                size += 1
                head = head.getNext()
            return size

        size = getLinkedListSize(head)

        num_blocks = math.ceil(math.sqrt(size))
        block_size = math.ceil(size / num_blocks)

        blocks = []  # using List as Stack
        head_cpy, cur = head, 0
        for cur in range(size):
            if cur % block_size == 0:
                blocks.append(head_cpy)
            head_cpy = head_cpy.getNext()

        for i in range(num_blocks - 1, 0 - 1, -1):
            self.printLinkedListInReverseDirect(blocks[i], block_size)


    """
        
    """

    def printLinkedListInReverseDirect(self, head, size):
        if size:
            self.printLinkedListInReverseDirect(head.getNext(), size - 1)
            head.printValue()

    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:
        def getLinkedListSize(head):
            size = 0
            while head != None:
                size += 1
                head = head.getNext()
            return size

        size = getLinkedListSize(head)
        self.printLinkedListInReverseDecomposition(head, size, t=3)

    def printLinkedListInReverseDecomposition(self, head, size, t):
        if size == 1:
            head.printValue()
            return
        num_blocks = math.ceil(size ** (1 / t))  # at least two blocks.
        block_size = math.ceil(size / num_blocks)

        blocks = []  # using List as Stack

        head_cpy, cur = head, 0

        for cur in range(size):
            if cur % block_size == 0:
                blocks.append(head_cpy)
            head_cpy = head_cpy.getNext()

        for i in range(num_blocks - 1, 0 - 1, -1):
            nxt_size = block_size
            if i == num_blocks - 1:
                nxt_size = cur % block_size + 1

            if t == 2:
                self.printLinkedListInReverseDirect(blocks[i], nxt_size)
            else:
                self.printLinkedListInReverseDecomposition(blocks[i], nxt_size, t - 1)

    """
        divide and conquer
        Divide into two parts print the right part first using this algorithm again.
    """

    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:
        def getLinkedListSize(head):
            size = 0
            while head != None:
                size += 1
                head = head.getNext()
            return size

        def helper(head, n):
            if n > 1:
                half = head
                for _ in range(n // 2):
                    half = half.getNext()
                helper(half, n - n // 2)
                helper(head, n // 2)
            elif n != 0:
                head.printValue()

        size = getLinkedListSize(head)
        helper(head, size)