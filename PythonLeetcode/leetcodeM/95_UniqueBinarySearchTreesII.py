"""
95. Unique Binary Search Trees II

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

``
class GenerateNumTrees:

    def doit_dp(self, n: int) -> list[TreeNode]:
        """
        :type n: int
        :rtype: List[TreeNode]
        """
        def helper(start, end):
            if (start, end) in memo:
                return memo[start, end]

            tree = []
            for root in range(start, end + 1):

                left_list = helper(start, root - 1)
                right_list = helper(root + 1, end)

                for left in left_list:
                    for right in right_list:
                        node = TreeNode(root)
                        node.left = left
                        node.right = right
                        tree.append(node)

            memo[start, end] = tree or [None]
            return tree or [None]

        memo = {}
        if n == 0:
            return []
        return helper(1, n)

    def doit_divide_conquer(self, n: int) -> list[TreeNode]:
        # divide and conquer
        def rec(start, end):
            curr_res = []
            if start > end:
                curr_res.append(None)
                return curr_res
            # if start == end:
            #     curr_res.append(TreeNode(start))
            #     return curr_res

            for i in range(start, end + 1):
                left = rec(start, i - 1)
                right = rec(i + 1, end)

                for l in left:
                    for r in right:
                        n = TreeNode(i, l, r)
                        curr_res.append(n)
            return curr_res

        if n == 0:
            return []

        return rec(1, n)