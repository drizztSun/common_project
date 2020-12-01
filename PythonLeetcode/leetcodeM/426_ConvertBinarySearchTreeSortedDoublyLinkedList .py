"""
426. Convert Binary Search Tree to Sorted Doubly Linked List

Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list.
For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor,
and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.



Example 1:



Input: root = [4,2,5,1,3]


Output: [1,2,3,4,5]

Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

Example 2:

Input: root = [2,1,3]
Output: [1,2,3]
Example 3:

Input: root = []
Output: []
Explanation: Input is an empty tree. Output is also an empty Linked List.
Example 4:

Input: root = [1]
Output: [1]


Constraints:

-1000 <= Node.val <= 1000
Node.left.val < Node.val < Node.right.val
All values of Node.val are unique.
0 <= Number of Nodes <= 2000

"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""


class TreeToDoublyList:

    """
    Complexity Analysis

    Time complexity : \mathcal{O}(N)O(N) since each node is processed exactly once.

    Space complexity : \mathcal{O}(N)O(N). We have to keep a recursion stack of the size of the tree height,
    which is \mathcal{O}(\log N)O(logN) for the best case of completely balanced tree and \mathcal{O}(N)O(N) for the worst case of completely unbalanced tree

    """
    def doit_search(self, root: 'Node') -> 'Node':
        if not root:
            return None

        def helper(root):
            nonlocal last, first
            if root is None:
                return None

            helper(root.left)

            if last:
                last.right = root
                root.left = last
            else:
                first = root

            last = root

            helper(root.right)

        last, first = None, None

        helper(root)
        last.right = first
        first.left = last
        return first

    def doit_(self, root: 'Node') -> 'Node':

        if not root:
            return root

        def dfs(node):

            if not node:
                return None, None

            lh, lt = dfs(node.left)

            rh, rt = dfs(node.right)

            h, t = node, node

            if lh and lt:
                lt.right, h.left = h, lt
                h = lh

            if rh and rt:
                t.right, rh.left = rh, t
                t = rt

            return h, t

        h, t = dfs(root)
        h.left, t.right = t, h

        return h
