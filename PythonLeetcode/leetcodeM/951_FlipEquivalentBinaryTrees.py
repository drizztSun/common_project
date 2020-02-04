# 951. Flip Equivalent Binary Trees


# For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.

# A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.

# Write a function that determines whether two binary trees are flip equivalent.  The trees are given by root nodes root1 and root2.


# Example 1:

# Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
# Output: true
# Explanation: We flipped at nodes with values 1, 3, and 5.
# Flipped Trees Diagram


# Note:

# Each tree will have at most 100 nodes.
# Each value in each tree will be a unique integer in the range [0, 99].


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):

        self.val = x
        self.left = None
        self.right = None


"""
Approach 1: Recursion
Intuition

If root1 and root2 have the same root value, then we only need to check if their children are equal (up to ordering.)

Algorithm

There are 3 cases:

If root1 or root2 is null, then they are equivalent if and only if they are both null.

Else, if root1 and root2 have different values, they aren't equivalent.

Else, let's check whether the children of root1 are equivalent to the children of root2. There are two different ways to pair these children.

Complexity Analysis

Time Complexity: O(min(N_1, N_2)), where N_1, N_2 are the lengths of root1 and root2.

Space Complexity: O(min(H_1, H_2)), where H_1, H_2 are the heights of the trees of root1 and root2.

"""


class FlipEquiv:

    def doit(self, root1, root2):

        def search(n1, n2):

            if not n1 and not n2:
                return True

            if any([not n1, not n2]):
                return False

            if n1.val != n2.val:
                return False

            return (search(n1.left, n2.right) and search(n1.right, n2.left)) or (search(n1.left, n2.left) and search(n1.right, n2.right))

        return search(root1, root2)


if __name__ == '__main__':

    r1 = TreeNode(1)
    r1.left = TreeNode(2)
    r1.left.left = TreeNode(4)
    r1.left.right = TreeNode(5)
    r1.left.right.left = TreeNode(7)
    r1.left.right.right = TreeNode(8)

    r1.right = TreeNode(3)
    r1.right.left = TreeNode(6)

    r2 = TreeNode(1)
    r2.right = TreeNode(2)
    r2.right.left = TreeNode(4)
    r2.right.right = TreeNode(5)
    r2.right.right.left = TreeNode(8)
    r2.right.right.right = TreeNode(7)

    r2.left = TreeNode(3)
    r2.left.right = TreeNode(6)

    res = FlipEquiv().doit(r1, r2)

    pass
