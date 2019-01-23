# 700. Search in a Binary Search Tree

# Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's value equals the given value.
# Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.

# For example, 

# Given the tree:
#         4
#        / \
#       2   7
#      / \
#     1   3

# And the value to search: 2
# You should return this subtree:

#       2     
#      / \   
#     1   3
# In the example above, if we want to search the value 5, since there is no node with value 5, we should return NULL.

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class SearchBST:

    def doit(self, root, val):
        """
        :type root: TreeNode
        :type val: int
        :rtype: TreeNode
        """
        node = root
        
        while node:
            
            if node.val == val:
                return node
            
            elif node.val > val:
                node = node.left
            
            else:
                node = node.right
        
        return node
        



if __name__ == "__main__":

    p = TreeNode(4)
    p.left = TreeNode(2)
    p.right = TreeNode(7)
    p.left.left = TreeNode(1)
    p.left.right = TreeNode(3)

    res = SearchBST().doit(p)

        