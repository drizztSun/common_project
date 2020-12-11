"""
1302. Deepest Leaves Sum

Given a binary tree, return the sum of values of its deepest leaves.


Example 1:



Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15


Constraints:

The number of nodes in the tree is between 1 and 10^4.
The value of nodes is between 1 and 100.
"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class DeepestLeavesSum:

    def doit_search(self, root: 'TreeNode') -> int:

        depth, sums = 0, 0

        def search(node, dep):
            nonlocal depth, sums
            if not node.left and not node.right:
                if dep == depth:
                    sums += node.val
                elif dep > depth:
                    depth = dep
                    sums = node.val
                return

            if node.left:
                search(node.left, dep + 1)

            if node.right:
                search(node.right, dep + 1)

        search(root, 0)
        return sums