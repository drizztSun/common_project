# 530. Minimum Absolute Difference in BST

# Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

# Example:

# Input:

#    1
#     \
#      3
#     /
#    2

# Output:
# 1
# 
# Explanation:
# The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
# Note: There are at least two nodes in this BST.


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

import math

class MinimunAbsoluteDiffInBST(object):

    # in-order
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        node, buff, res = root, [], []

        while node or buff:

            if node:
                buff.append(node)
                node = node.left
            else:
                res.append(buff[-1].val)
                node.buff[-1].right
                buff.pop()

        
        return min(map(lambda x, y: math.fabs(x - y), res))

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def inorder_search(root):
            
            node, buff = root, []
            while node or buff:
                if node:
                    buff.append(node)
                    node = node.left
                else:
                    n = buff.pop()
                    yield n.val
                    node = n.right
                    
        res, prev = float('inf'), None
        for c in inorder_search(root):
            if prev is not None:
                res = min(res, abs(c - prev))
        
            prev = c
                        
        return res





if __name__ == "__main__":

    root = TreeNode(236)
    root.left = TreeNode(104)
    root.left.right = TreeNode(227)

    root.right = TreeNode(701)
    root.right.right = TreeNode(911)

    res = MinimunAbsoluteDiffInBST().doit(root)

    pass