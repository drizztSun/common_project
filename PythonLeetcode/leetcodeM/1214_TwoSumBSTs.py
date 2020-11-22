"""
1214. Two Sum BSTs

Given two binary search trees, return True if and only if there is a node in the first tree and a node in the second tree
whose values sum up to a given integer target.



Example 1:



Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
Output: true
Explanation: 2 and 3 sum up to 5.
Example 2:



Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
Output: false


Constraints:

Each tree has at most 5000 nodes.
-10^9 <= target, node.val <= 10^9

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class twoSumBSTs:

    def doit_BST(self, root1, root2, target):

        def dfs(n1, n2, memo):

            if not n1 or not n2:
                return False

            if (n1, n2) in memo:
                return memo[(n1, n2)]

            if n1.val + n2.val == target:
                return True

            elif n1.val + n2.val > target:
                memo[(n1, n2)] = dfs(n1.left, n2, memo) or dfs(n1, n2.left, memo)

            else:
                memo[(n1, n2)] = dfs(n1.right, n2, memo) or dfs(n1, n2.right, memo)

            return memo[(n1, n2)]

        return dfs(root1, root2, {})