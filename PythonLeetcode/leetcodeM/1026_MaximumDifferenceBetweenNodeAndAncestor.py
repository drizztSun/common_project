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


    def doit_1(self, root: TreeNode) -> int:
        if not root: return 0
        # record the required maximum difference
        result = 0

        def helper(node, cur_max, cur_min):
            nonlocal result

            if not node: return
            # update `result`
            result = max(result, abs(cur_max - node.val), abs(cur_min - node.val))
            # update the max and min
            cur_max = max(cur_max, node.val)
            cur_min = min(cur_min, node.val)
            helper(node.left, cur_max, cur_min)
            helper(node.right, cur_max, cur_min)

        helper(root, root.val, root.val)
        return result

    """
    Approach #2: Maximum Minus Minimum
    Intuition

    An insight is that:

    Given any two nodes on the same root-to-leaf path, they must have the required ancestor relationship.
    Therefore, we just need to record the maximum and minimum values of all root-to-leaf paths and return the maximum difference.

    To achieve this, we can record the maximum and minimum values during the recursion and return the difference when encountering leaves.

    Algorithm

    Step 1: Define a function helper, which takes three arguments as input and returns an integer.

    The first argument node is the current node, and the second argument cur_max and third argument cur_min are the maximum and minimum values along the root to the current node, respectively.

    Function helper returns cur_max - cur_min when encountering leaves. Otherwise, it calls helper on the left and right subtrees and returns their maximum.

    Step 2: Run helper on the root and return the result.

    Implementation

    """
    def doit_2(self, root: TreeNode) -> int:
        if not root:
            return 0

        def helper(node, cur_max, cur_min):
            # if encounter leaves, return the max-min along the path
            if not node:
                return cur_max - cur_min
            # else, update max and min
            # and return the max of left and right subtrees
            cur_max = max(cur_max, node.val)
            cur_min = min(cur_min, node.val)
            left = helper(node.left, cur_max, cur_min)
            right = helper(node.right, cur_max, cur_min)
            return max(left, right)

        return helper(root, root.val, root.val)

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