"""
285. Inorder Successor in BST

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

The successor of a node p is the node with the smallest key greater than p.val.



Example 1:


Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.
Example 2:


Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.


Note:

If the given node has no in-order successor in the tree, return null.
It's guaranteed that the values of the tree are unique.


"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class InorderSuccessor:

    """
    Approach 1: Iterative Inorder Traversal

    Successor is the smallest node in the inorder traversal after the current one.

    There could be two situations :

    If the node has a right child, the successor is somewhere lower in the tree, see red nodes on the Fig. below.

    Otherwise, the successor is somewhere upper in the tree, see blue nodes on the Fig.

    Complexity Analysis

    Time complexity :O(Hp) in the best case, when node p has a right child. Here O(Hp) is a height of node p. O(H) in the worst case of no right child. Here HH is a tree height.

    Space complexity : O(1) in the best case, when node p has a right child. Otherwise, up to O(H) to keep the stack.
    """
    def doit_search_1(self, root: 'TreeNode', p: 'TreeNode') -> 'TreeNode':
        # the successor is somewhere lower in the right subtree
        # successor: one step right and then left till you can
        if p.right:
            p = p.right
            while p.left:
                p = p.left
            return p

        # the successor is somewhere upper in the tree
        stack, inorder = [], float('-inf')

        # inorder traversal : left -> node -> right
        while stack or root:
            # 1. go left till you can
            while root:
                stack.append(root)
                root = root.left

            # 2. all logic around the node
            root = stack.pop()
            if inorder == p.val:  # if the previous node was equal to p
                return root  # then the current node is its successor
            inorder = root.val

            # 3. go one step right
            root = root.right

        # there is no successor
        return None

    def doit_search(self, root: 'TreeNode', p: 'TreeNode') -> 'TreeNode':

        res, pres = float('inf'), None

        def search(node):
            nonlocal res, pres
            if not node:
                return

            if node.val > p.val and node.val - p.val < res:
                res = node.val - p.val
                pres = node

            if node.val > p.val:
                search(node.left)

            elif node.val <= p.val:
                search(node.right)

        search(root)
        return pres


