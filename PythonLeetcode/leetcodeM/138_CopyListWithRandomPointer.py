"""
138. Copy List with Random Pointer


A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

The Linked List is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) where random pointer points to, or null if it does not point to any node.


Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
Example 4:

Input: head = []
Output: []
Explanation: Given linked list is empty (null pointer), so return null.


Constraints:

-10000 <= Node.val <= 10000
Node.random is null or pointing to a node in the linked list.
The number of nodes will not exceed 1000.
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random


class CopyRandomList:

    def doit_link(self, head: 'Node') -> 'Node':

        if not head:
            return head

        buff = []
        newhead = Node()
        node, newnode = head, newhead
        newbuff = []

        while node:
            newnode.next = Node(node.val)
            buff.append(node)
            newbuff.append(newnode.next)
            node, newnode = node.next, newnode.next

        ref2id = {c : i for i, c in enumerate(buff)}

        node, newnode = head, newhead.next
        while node:
            newnode.random = newbuff[ref2id[node.random]] if node.random else None
            node, newnode = node.next, newnode.next

        return newhead.next

    def doit_best(self, head: 'Node') -> 'Node':
        if not head:
            return head
        referenceNodes = {}
        currNode = head
        currCopyHead = currCopyNode = Node(currNode.val)

        referenceNodes[currNode] = currCopyNode

        # Create and save the nodes of the new list
        while (currNode.next):
            nextNode = currNode.next
            nextCopyNode = Node(nextNode.val)

            currCopyNode.next = nextCopyNode

            referenceNodes[nextNode] = nextCopyNode

            currNode = nextNode
            currCopyNode = nextCopyNode

        # Create links between nodes and their random pointers
        while (head):
            if (head.random):
                referenceNodes[head].random = referenceNodes[head.random]
            head = head.next

        return currCopyHead