# 1026. Maximum Difference Between Node and Ancestor

# Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.

# (A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)


# Example 1:


# Input: [8,3,10,1,6,null,14,null,null,4,7,13]
# Output: 7
# Explanation:
# We have various ancestor-node differences, some of which are given below :
# |8 - 3| = 5
# |3 - 7| = 4
# |8 - 1| = 7
# |10 - 13| = 3
# Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class MaxAncestorDiff:

    def doit(self, root):

        def cal(node):

            if not node.left and not node.right:
                return node.val, node.val, 0

            lmax, lmin, ldiff = float('-inf'), float('inf'), 0
            if node.left:
                lmax, lmin, ldiff = cal(node.left)


            rmax, rmin, rdiff = float('-inf'), float('inf'), 0
            if node.right:
                rmax, rmin, rdiff =  cal(node.right)

            b, s = max(lmax, rmax), min(lmin, rmin)

            return max(b, node.val), min(s, node.val), max(ldiff, rdiff, abs(b - node.val), abs(s - node.val))

        return cal(root)[2]


if __name__ == '__main__':

    root = TreeNode(8)
    root.left = TreeNode(3)
    root.right = TreeNode(10)

    root.left.left = TreeNode(1)
    root.left.right = TreeNode(6)
    root.left.right.left = TreeNode(4)
    root.left.right.right = TreeNode(7)

    root.right.right = TreeNode(14)
    root.right.right.left = TreeNode(13)

    res = MaxAncestorDiff().doit(root)


    root = TreeNode(2)
    root.right = TreeNode(0)
    root.right.left = TreeNode(1)

    res = MaxAncestorDiff().doit(root)

    pass
