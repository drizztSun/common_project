#  Merge Two Binary Trees

#Given two binary trees and imagine that when you put one of them to cover the other, 
#some nodes of the two trees are overlapped while the others are not.

#You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, 
#then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

#Example 1:
#Input: 
#	Tree 1                     Tree 2                  
#          1                         2                             
#         / \                       / \                            
#        3   2                     1   3                        
#       /                           \   \                      
#      5                             4   7                  
#Output: 
#Merged tree:
#	     3
#	    / \
#	   4   5
#	  / \   \ 
#	 5   4   7



class TreeNode:

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class MergeTrees:
    def doit(self, t1, t2):
        """
        :type t1: TreeNode
        :type t2: TreeNode
        :rtype: TreeNode
        """
        def build(n1, n2):
            if not n1 and not n2:
                return None
            
            
            n = TreeNode((n1.val if n1 else 0) + (n2.val if n2 else 0))
            
            n.left = build(n1.left if n1 else None, n2.left if n2 else None)
            n.right = build(n1.right if n1 else None, n2.right if n2 else None)
            
            return n
        
        return build(t1, t2)



    def doit1(self, t1, t2):
        """
        :type t1: TreeNode
        :type t2: TreeNode
        :rtype: TreeNode
        """
        def build(n1, n2):

            if not n1:
                return n2
            
            if not n2:
                return n1

            n = TreeNode(n1.val + n2.val)
            n.left = build(n1.left, n2.left)
            n.right = build(n2.right, n2.right)

            return n

        return build(t1, t2)            
