"""
114. Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6



"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Flatten:

    def doit_dfs(self, root: 'TreeNode') -> None:
        """
        Do not return anything, modify root in-place instead.
        """

        def build(node):

            if not node:
                return None, None

            lh, lt = build(node.left)

            rh, rt = build(node.right)

            h, t = node, node

            node.left = None

            if lh and lt:
                h.right, t = lh, lt

            if rh and rt:
                t.right, t = rh, rt

            return h, t

        return build(root)[0]