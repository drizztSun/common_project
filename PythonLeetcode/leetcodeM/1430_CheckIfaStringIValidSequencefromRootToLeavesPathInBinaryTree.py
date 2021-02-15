"""
1430. Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree


Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree.

We get the given string from the concatenation of an array of integers arr and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.



Example 1:



Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
Output: true
Explanation:
The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure).
Other valid sequences are:
0 -> 1 -> 1 -> 0
0 -> 0 -> 0
Example 2:



Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
Output: false
Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.
Example 3:



Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
Output: false
Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.


Constraints:

1 <= arr.length <= 5000
0 <= arr[i] <= 9
Each node's value is between [0 - 9].

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class IsValidSequence:

    def doit_(self, root: 'TreeNode', arr: list) -> bool:

        def search(node, i):

            if not node:
                return False

            if i == len(arr): return False

            if arr[i] != node.val: return False

            if not node.left and not node.right: return i == len(arr) - 1

            return search(node.left, i + 1) or search(node.right, i + 1)

        return search(root, 0)

    def isValidSequence(self, root, arr: list) -> bool:

        def dfs(root, i):
            if not root or i == len(arr) or root.val != arr[i]:
                return False
            elif i == len(arr) - 1 and root.left is None and root.right is None:
                return True
            return dfs(root.left, i + 1) or dfs(root.right, i + 1)

        return dfs(root, 0)