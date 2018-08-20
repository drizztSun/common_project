import os




# leetcode 230. Kth Smallest Element in a BST
# Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

# Note: 
# You may assume k is always valid, 1 ? k ? BST's total elements.

# Follow up:
# What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently?
# How would you optimize the kthSmallest routine?


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class kthSmallest:

    def doit1(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        # in-order trans, stop when visited k element
        def inorder(root):
            nonlocal n_visited, val_k, flag_stop
            if root == None:
                return
            
            inorder(root.left)

            if not flag_stop:
                n_visited += 1

                if n_visited == k:
                    val_k = root.val
                    flag_stop = True
                    return

                inorder(root.right)
        
        n_visited = 0
        val_k = None
        flag_stop = False
        
        inorder(root)
        
        return val_k

    def doit1(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        def search(node):
            if not node:
                return []

            res = search(node.left) + [node.val] + search(node.right)

            return res

        res = search(root)
        return None if len(res) < k else res[k-1]         
            
    def doit(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        cur, buff, res = root, [], []

        while cur:

            if cur.left:
                buff.append(cur)
                cur = cur.left
            else :
                res.append(cur)
                while not cur.right:
                    cur = buff.pop()
                    res.append(cur)

                cur = cur.right                        
                
            if len(res) >= k:
                return res[k-1].val

        return 0
        
# leetcode 671. Second Minimum Node In a Binary Tree        
# Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.
# Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
# If no such second minimum value exists, output -1 instead.

# Example 1:
# Input: 
#    2
#   / \
#  2   5
#     / \
#    5   7
# Output: 5
# Explanation: The smallest value is 2, the second smallest value is 5.    


# Example 2:
# Input: 
#    2
#   / \
#  2   2

# Output: -1
# Explanation: The smallest value is 2, but there isn't any second smallest value.



if __name__=="__main__":

    


    pass
        