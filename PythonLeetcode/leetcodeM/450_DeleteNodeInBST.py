"""
450. Delete Node in a BST

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Follow up: Can you solve it with time complexity O(height of tree)?



Example 1:


Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:

Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.
Example 3:

Input: root = [], key = 0
Output: []


Constraints:

The number of nodes in the tree is in the range [0, 104].
-105 <= Node.val <= 105
Each node has a unique value.
root is a valid binary search tree.
-105 <= key <= 105

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class DeleteBSTNode:

    def doit_search(self, root: 'TreeNode', key: int) -> 'TreeNode':

        def successor(root):
            """
            One step right and then always left
            """
            root = root.right
            while root.left:
                root = root.left
            return root.val

        def predecessor(root):
            """
            One step left and then always right
            """
            root = root.left
            while root.right:
                root = root.right
            return root.val

        def deleteNode(root: 'TreeNode', key: int) -> 'TreeNode':
            if not root:
                return None

            # delete from the right subtree
            if key > root.val:
                root.right = deleteNode(root.right, key)
            # delete from the left subtree
            elif key < root.val:
                root.left = deleteNode(root.left, key)
            # delete the current node
            else:
                # the node is a leaf
                if not (root.left or root.right):
                    root = None
                # the node is not a leaf and has a right child
                elif root.right:
                    root.val = successor(root)
                    root.right = deleteNode(root.right, root.val)
                # the node is not a leaf, has no right child, and has a left child
                else:
                    root.val = predecessor(root)
                    root.left = deleteNode(root.left, root.val)

            return root

        return deleteNode(root, key)

    def doit_search(self, root: 'TreeNode', key: int) -> 'TreeNode':

        prev, node = None, root
        while node:
            if node.val == key:
                break
            elif node.val > key:
                prev, node = node, node.left
            else:
                prev, node = node, node.right

        if not node:
            return root

        if node.left and node.right:
            rightOne = node.right

            while rightOne.left:
                rightOne = rightOne.left

            rightOne.left = node.left

        childNode = node.right if node.right else node.left

        # root has key
        if prev == None:
            return childNode

        if prev.val < key:
            prev.right = childNode
        else:
            prev.left = childNode

        node.left, node.right = None, None

        return root