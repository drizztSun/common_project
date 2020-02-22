# 1022. Sum of Root To Leaf Binary Numbers

# Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path represents a binary number starting with the most significant bit.  For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.

# For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.

# Return the sum of these numbers.


# Example 1:

# Input: [1, 0, 1, 0, 1, 0, 1]
# Output: 22
# Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

# Note:

# The number of nodes in the tree is between 1 and 1000.
# node.val is 0 or 1.
# The answer will not exceed 2 ^ 31 - 1.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class SumRootToLeaf:

    def doit(self, root):
        def build(n):

            if not n.left and not n.right:
                return [str(n.val)]

            ans = []
            if n.left:
                ans.extend([str(n.val) + c for c in build(n.left)])

            if n.right:
                ans.extend([str(n.val) + c for c in build(n.right)])

            return ans

        res = 0
        for c in build(root):
            t = 0
            for i in range(len(c)):
                if c[i] == '1':
                    t += 2 ** (len(c) - 1 - i)
            res += t

        return res

    def doit(self, root):

        def helper(node, partial_sum=0):
            if not node:
                return 0
            partial_sum = partial_sum * 2 + node.val
            # leaf node
            if not node.left and not node.right:
                return partial_sum
            # non-leaf node
            return helper(node.left, partial_sum) + helper(node.right, partial_sum)

        return helper(root)


if __name__ == '__main__':

    root = TreeNode(1)
    root.left = TreeNode(0)
    root.right = TreeNode(1)

    root.left.left = TreeNode(0)
    root.left.right = TreeNode(1)

    root.right.left = TreeNode(0)
    root.right.right = TreeNode(1)

    res = SumRootToLeaf().doit(root)
