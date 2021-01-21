"""
# 998. Maximum Binary Tree II

# We are given the root node of a maximum tree: a tree where every node has a value greater than any other value in its subtree.

# Just as in the previous problem, the given tree was constructed from an list A (root = Construct(A)) recursively with the following Construct(A) routine:

# If A is empty, return null.
# Otherwise, let A[i] be the largest element of A.  Create a root node with value A[i].
# The left child of root will be Construct([A[0], A[1], ..., A[i-1]])
# The right child of root will be Construct([A[i+1], A[i+2], ..., A[A.length - 1]])
# Return root.
# Note that we were not given A directly, only a root node root = Construct(A).

# Suppose B is a copy of A with the value val appended to it.  It is guaranteed that B has unique values.

# Return Construct(B).


# Example 1:


# Input: root = [4,1,3,null,null,2], val = 5
# Output: [5,4,null,1,3,null,null,2]
# Explanation: A = [1,4,2,3], B = [1,4,2,3,5]

# Example 2:


# Input: root = [5,2,4,null,1], val = 3
# Output: [5,2,4,null,1,null,3]
# Explanation: A = [2,1,5,4], B = [2,1,5,4,3]

# Example 3:


# Input: root = [5,2,3,null,1], val = 4
# Output: [5,2,4,null,1,3]
# Explanation: A = [2,1,5,3], B = [2,1,5,3,4]
"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class InsertIntoMaxTree:

    def doit_(self, root, val):

        target = TreeNode(val)
        
        parent, cur = None, root
        
        while cur and cur.val > val:
            parent, cur = cur, cur.right
        
        if not parent:
            root, target.left = target, root
        else:
            parent.right, target.left = target, cur
            
        return root

    def doit_recursive(self, root, val):

        def search(node, parent):

            if not node: return TreeNode(val)
            
            if node.val < val:
                tmp = TreeNode(val)
                tmp.left = node
                
                return tmp
            else:
                node.right = search(node.right, node)
                return node
            
        return search(root, None)


if __name__ == '__main__':

    r = TreeNode(4)
    r.left = TreeNode(1)
    r.right = TreeNode(3)
    r.right.left = TreeNode(2)

    res = InsertIntoMaxTree().doit(r, 5)

    r = TreeNode(5)
    r.left = TreeNode(2)
    r.right = TreeNode(4)
    r.left.right = TreeNode(1)

    res = InsertIntoMaxTree().doit(r, 3)

    r = TreeNode(5)
    r.left = TreeNode(2)
    r.right = TreeNode(3)
    r.left.right = TreeNode(1)

    res = InsertIntoMaxTree().doit(r, 4)

    pass
