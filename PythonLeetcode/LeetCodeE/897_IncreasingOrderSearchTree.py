# 897. Increasing Order Search Tree

# Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree,
# and every node has no left child and only 1 right child.

# Example 1:
# Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

#        5
#       / \
#     3    6
#    / \    \
#  2   4    8
# /        / \
# 1        7   9

# Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

# 1
#  \
#   2
#    \
#     3
#      \
#       4
#        \
#         5
#          \
#           6
#            \
#             7
#              \
#               8
#                \
#                 9
# Note:

# The number of nodes in the given tree will be between 1 and 100.
# Each node will have a unique integer value from 0 to 1000.

# Definition for a binary tree node.


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class IncreasingBST:
    def doit(self, root):
        if not root:
            return root

        def dfs(n):
            if n == None:
                return []
            return dfs(n.left) + [n] + dfs(n.right)

        A = dfs(root)
        head, tail = None, None
        for i in range(len(A)):
            A[i].left, A[i].right = None, None
            if i == 0:
                head, tail = A[i], A[i]
            else:
                tail.right = A[i]
                tail = tail.right

        return head

    def doit(self, root):
        def walk(n, tail):
            if not n:
                return tail
            left = walk(n.left, n)
            n.left = None
            n.right = walk(n.right, tail)
            return left

        return walk(root, None)


if __name__ == '__main__':

    r = TreeNode(5)
    r.left = TreeNode(3)

    r.left.left = TreeNode(2)
    r.left.right = TreeNode(4)
    r.left.left.left = TreeNode(3)

    r.right = TreeNode(6)
    r.right.right = TreeNode(8)
    r.right.right.left = TreeNode(7)
    r.right.right.right = TreeNode(9)

    res = IncreasingBST().doit(r)
