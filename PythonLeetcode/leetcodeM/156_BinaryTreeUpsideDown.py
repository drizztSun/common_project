"""
156. Binary Tree Upside Down

Given the root of a binary tree, turn the tree upside down and return the new root.

You can turn a binary tree upside down with the following steps:

The original left child becomes the new root.
The original root becomes the new right child.
The original right child becomes the new left child.


The mentioned steps are done level by level, it is guaranteed that every node in the given tree has either 0 or 2 children.



Example 1:


Input: root = [1,2,3,4,5]
Output: [4,5,2,null,null,3,1]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]


Constraints:

The number of nodes in the tree will be in the range [0, 10].
1 <= Node.val <= 10
Every node has either 0 or 2 children.

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class UpsideDownBinaryTree:

    def doit_(self, root: 'TreeNode') -> 'TreeNode':

        if not root:
            return None

        def traversel(node):

            if not node.left:
                return node, node

            rootl, lefttail = traversel(node.left)
            rootr, righttail = traversel(node.right) if node.right else (None, None)

            node.left = node.right = None

            lefttail.left = rootr
            lefttail.right = node

            return rootl, node

        return traversel(root)[0]