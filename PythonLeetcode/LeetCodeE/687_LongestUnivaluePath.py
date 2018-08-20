


# 687. Longest Univalue Path


# Given a binary tree, find the length of the longest path where each node in the path has the same value.
# This path may or may not pass through the root.

# Note: The length of path between two nodes is represented by the number of edges between them.

# Example 1:

# Input:

#              5
#             / \
#            4   5
#           / \   \
#          1   1   5
# Output:
# 2

# Example 2:

# Input:

#              1
#             / \
#            4   5
#           / \   \
#          4   4   5
# Output:
# 2

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class longestUnivaluePath:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        


if __name__=="__main__":

    

    res = longestUnivaluePath().doit()