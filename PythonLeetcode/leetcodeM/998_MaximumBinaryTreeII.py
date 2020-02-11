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

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class InsertIntoMaxTree:

    def doit(self, root, val):

        st = []
        n = root

        while n and n.val > val:
            st.append(n)
            n = n.right

        if st:
            st[-1].right = TreeNode(val)
            st[-1].right.left = n
        else:
            st.append(TreeNode(val))
            st[0].left = root

        return st[0]

    def doit(self, root, val):

        x = TreeNode(val)
        if not root or root.val < val:
            x.left = root
            return x

        p = root
        while True:
            if not p.right:
                p.right = x
                return root
            if p.right.val < val:
                x.left = p.right
                p.right = x
                return root
            p = p.right

    def doit(self, root, val):

        def search(n, p):
            if not n or n.val < val:
                p.right = TreeNode(val)
                p.right.left = n
                return

            search(n.right, n)

        if root and root.val < val:
            n = TreeNode(val)
            n.left = root
            root = n
        else:
            search(root, None)

        return root


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
