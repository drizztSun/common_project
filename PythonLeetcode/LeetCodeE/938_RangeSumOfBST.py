# 938. Range Sum of BST

# Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive).

# The binary search tree is guaranteed to have unique values.


# Example 1:

# Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
# Output: 32

# Example 2:

# Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
# Output: 23


# Note:

# The number of nodes in the tree is at most 10000.
# The final answer is guaranteed to be less than 2^31.

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class RangeSumBST:

    def doit(self, root, L, R):

        def search(node):

            if not node:
                return 0

            n = 0

            if node.val <= R:
                n += search(node.right)

            if node.val >= L:
                n += search(node.left)

            if L <= node.val <= R:
                n += node.val

            return n

        return search(root)

    def doit(self, root, L, R):

        buff = [root]
        ans = 0

        while buff:

            node = buff.pop()

            if L <= node.val <= R:
                ans += node.val

            if node.val > L and node.left:
                buff.append(node.left)

            if node.val < R and node.right:
                buff.append(node.right)

        return ans
