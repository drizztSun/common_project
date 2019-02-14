# 669. Trim a Binary Search Tree

# Given a binary search tree and the lowest and highest boundaries as L and R, 
# trim the tree so that all its elements lies in [L, R] (R >= L). 
# You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

#Example 1:
#Input: 
#    1
#   / \
#  0   2

#  L = 1
#  R = 2

#Output: 
#    1
#      \
#       2
#Example 2:
#Input: 
#    3
#   / \
#  0   4
#   \
#    2
#   /
#  1

#  L = 1
#  R = 3

#Output: 
#      3
#     / 
#   2   
#  /
# 1


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class TrimBST:


# Algorithm

# When \text{node.val > R}node.val > R, we know that the trimmed binary tree must occur to the left of the node. 
# Similarly, when \text{node.val < L}node.val < L, the trimmed binary tree occurs to the right of the node. 
# Otherwise, we will trim both sides of the tree.

# Complexity Analysis

# Time Complexity: O(N)O(N), where NN is the total number of nodes in the given tree. We visit each node at most once.

# Space Complexity: O(N)O(N). Even though we don't explicitly use any additional memory, 
# the call stack of our recursion could be as large as the number of nodes in the worst case.
    
    def doit(self, root: 'TreeNode', L: 'int', R: 'int') -> 'TreeNode':

        def trim(node, L, R):

            if not node:
                return node

            if node.val < L:
                return trim(node.right)

            if node.val > R:
                return trim(node.left)

            node.left = trim(node.left)
            node.right = trim(node.right)

            return node

        return trim(root)

    
    def doit1(self, root, L, R):

        node = root
        while node and not L <= node.val <= R:
            if node.val < L:
                node = node.right
            else :
                node = node.left

        if not node:
            return node

        node.left = self.doit1(node.left, L, node.val)
        node.right = self.doit1(node.right, node.val, R)

        return node       