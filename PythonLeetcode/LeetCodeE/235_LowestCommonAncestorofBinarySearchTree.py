"""

235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the
lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).


Example 1:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2


Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the BST.

"""


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class lowestCommonAncestor(object):
    def doit(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """

        pt = root
        while pt:
            if pt.val > p.val and pt.val > q.val:
               pt = pt.left
            elif pt.val < p.val and pt.val < q.val:
               pt = pt.right
            else:
               break 

        return pt

    def doit2(self, root, p, q):

        def search(root, p, q):
            left = min(p.val,q.val)
            right = max(p.val,q.val)

            if root.val == left or root.val == right:
                return root.val
            if root.val > left and root.val < right:
                return root.val
            if root.val < left and root.val < right:
                return search(root.right, p, q)
            if root.val > left and root.val > right:
                return search(root.left, p, q)

        return search(root, p, q)


# Leetcode 236. Lowest Common Ancestor of a Binary Tree
class lowestCommonAncestorII(object):
    def doit(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        def search(node, p, q):
            if not node:
                return None

            res = None
            if node == p or node == q: 
                res = node

            resl = search(node.left, p, q)

            resr = search(node.right, p, q)


            if resl and resr:
                res = node
            elif resl or resr:
                res = node if res else (resl if resl else resr)

            return res         
    
        return search(root, p, q)

    # Best way
    def doit2(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        def search(node, p, q):
            if not node:
                return None
        
            if node == p or node == q:
                return node

            left = search(node.left, p, q)
            right = search(node.right, p, q)

            if left and right:
                return node

            return left if left else right

        return search(root, p, q)

        


if __name__=="__main__":


    a = TreeNode(1)
    a.right = TreeNode(2)

    res = lowestCommonAncestorII().doit(a, a, a.right)

    pass