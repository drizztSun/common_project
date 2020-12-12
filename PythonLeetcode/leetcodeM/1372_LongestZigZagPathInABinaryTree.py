"""
1372. Longest ZigZag Path in a Binary Tree

Given a binary tree root, a ZigZag path for a binary tree is defined as follow:

Choose any node in the binary tree and a direction (right or left).
If the current direction is right then move to the right child of the current node otherwise move to the left child.
Change the direction from right to left or right to left.
Repeat the second and third step until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.



Example 1:



Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
Output: 3
Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
Example 2:



Input: root = [1,1,1,null,1,null,null,1,1,null,1]
Output: 4
Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).
Example 3:

Input: root = [1]
Output: 0


Constraints:

Each tree has at most 50000 nodes..
Each node's value is between [1, 100].


"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class LongestZigZagPath:

    def doit_search(self, root) -> int:

        length = 0

        def search(node, lastdir, depth):
            nonlocal length

            if not node:
                return

            length = max(length, depth)

            if lastdir:
                search(node.left, not lastdir, depth + 1)
                search(node.right, lastdir, 1)
            else:
                search(node.left, lastdir, 1)
                search(node.right, not lastdir, depth + 1)

        search(root, True, 0)
        search(root, False, 0)

        return length

    def longestZigZag(self, root) -> int:

        def doZigZag(root, isRight, q):
            if not root:
                return 0
            next_branch = root.right if isRight else root.left
            other_branch = root.right if not isRight else root.left
            if other_branch:
                q.append((other_branch, isRight))
            return 1 + doZigZag(next_branch, not isRight, q)

        q = [(root.left, True), (root.right, False)]
        max_result = 0
        while q:
            curr_root, isRight = q.pop(0)
            if curr_root:
                max_result = max(max_result, doZigZag(curr_root, isRight, q))
        return max_result





