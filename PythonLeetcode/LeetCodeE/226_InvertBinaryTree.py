import os


# 226. Invert Binary Tree
# Invert a binary tree.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class invertTree:

    # do it on old one
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """

        def swap(node):
            if not node:
                return None

            node.left, node.right = node.right, node.left

            swap(node.left)
            swap(node.right)

            return node

        return swap(root)

    # create new one
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        def swap(node):
            if not root:
                return None

            node = TreeNode(root.val)
            node.right = swap(root.left)
            node.left = swap(root.right)

            return node

        return swap(root)

                

