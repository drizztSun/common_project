"""
98. Validate Binary Search Tree

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.


Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class ValidateBinarySearchTree:

    """
    Approach 3: Inorder traversal
    Algorithm

    Let's use the order of nodes in the inorder traversal Left -> Node -> Right.
    """
    def doit_search_3(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        stack, inorder = [], float('-inf')

        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            root = stack.pop()
            # If next element in inorder traversal
            # is smaller than the previous one
            # that's not BST.
            if root.val <= inorder:
                return False
            inorder = root.val
            root = root.right

        return True

    def doit_search_recursive(self, root) -> bool:
        """
        :type root: TreeNode
        :rtype: bool
        """

        def iterCheck(node, minVal, maxVal):
            if not node:
                return True

            if node.val >= maxVal or node.val <= minVal:
                return False

            return iterCheck(node.left, minVal, node.val) and iterCheck(node.right, node.val, maxVal)

        return iterCheck(root, float('-inf'), float('inf'))

    def doit_search_2(self, root) -> bool:

        def search(node):

            valid = True
            if not node.left and not node.right:
                return valid, node.val, node.val

            l, r = node.val, node.val
            if node.left:
                v, lmin, lmax = search(node.left)
                valid = v and node.val > lmax
                l, r = lmin, node.val

            if valid and node.right:
                v, rmin, rmax = search(node.right)
                valid = v and node.val < rmin
                l, r = min(l, node.val), rmax

            if not valid:
                return False, 0, 0

            return valid, l, r

        return search(root)[0]

