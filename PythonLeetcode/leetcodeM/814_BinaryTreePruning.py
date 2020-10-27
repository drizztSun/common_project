"""
814. Binary Tree Pruning


We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class PruneTree:

    def doit(self, root):

        def dfs(node):

            if not node.left and not node.right:
                return node.val == 0

            left = True if not node.left else dfs(node.left)
            right = True if not node.right else dfs(node.right)

            if left:
                node.left = None
            if right:
                node.right = None

            return left and right and node.val == 0

        dfs(root)

    def doit1(self, root):

        def recur(n):

            if n.left == None and n.right == None:
                return n.val == 0

            l, r = not n.left or recur(n.left), not n.right or recur(n.right)

            if l:
                n.left = None
            if r:
                n.right = None

            return l and r and n.val == 0

        return None if recur(root) else root