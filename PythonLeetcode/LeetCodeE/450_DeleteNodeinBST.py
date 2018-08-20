


# 450. Delete Node in a BST


# Given a root node reference of a BST and a key, delete the node with the given key in the BST.
# Return the root node reference (possibly updated) of the BST.

# Basically, the deletion can be divided into two stages:

# Search for a node to remove.
# If the node is found, delete the node.
# Note: Time complexity should be O(height of tree).

# Example:

# root = [5,3,6,2,4,null,7]
# key = 3

#    5
#   / \
#  3   6
# / \   \
# 2   4   7

# Given key to delete is 3. So we find the node with value 3 and delete it.

# One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

#    5
#   / \
#  4   6
# /     \
# 2       7

# Another valid answer is [5,2,6,null,4,null,7].

#    5
#   / \
#  2   6
#   \   \
#    4   7


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class deleteNode(object):

    def doit(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
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

        
    def doit1(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
        def maxC(root):
            while root.right:
                root = root.right
            return root 

        pre = None
        cur = root

        while cur and cur.val != key:
            pre = cur
            if cur.val < key:
                cur = cur.right
            else:
                cur = cur.left

        if cur is None: 
            return root
        
        ncur = cur.right
        if cur.left:
            ncur = cur.left
            maxC(cur.left).right = cur.right

        if pre is None: 
            return ncur

        if cur == pre.left: 
            pre.left = ncur
        else: 
            pre.right = ncur

        return root 
    

        

            
if __name__=="__main__":

    A = TreeNode(5)
    A.left, A.right = TreeNode(3), TreeNode(6)
    A.left.left, A.left.right = TreeNode(2), TreeNode(4)
    A.right.right = TreeNode(7)

    res = deleteNode().doit(A, 3)

    pass
    