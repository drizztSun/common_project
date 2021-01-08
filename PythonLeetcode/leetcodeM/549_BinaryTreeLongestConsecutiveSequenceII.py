"""
549. Binary Tree Longest Consecutive Sequence II


Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.

Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. 
On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.

Example 1:

Input:
        1
       / \
      2   3
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
 

Example 2:

Input:
        2
       / \
      1   3
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 

Note: All the values of tree nodes are in the range of [-1e7, 1e7].

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class LongestConsecutiveInBinaryTree:

    def doit_search(self, root: 'TreeNode') -> int:

        length = 0

        def search(node):
            nonlocal length

            if not node: return 0, 0

            li, ld = search(node.left)
            ri, rd = search(node.right)

            if node.left and abs(node.val - node.left.val) == 1:
                if node.val == node.left.val + 1:
                    ld += 1
                    li = 1
                else:
                    li += 1
                    ld = 1
            else:
                li, ld = 1, 1

            if node.right and abs(node.val - node.right.val) == 1:
                if node.val == node.right.val + 1:
                    rd += 1
                    ri = 1
                else:
                    ri += 1
                    rd = 1
            else:
                ri, rd = 1, 1

            length = max(length, ri + ld - 1, rd + li - 1)

            return max(ri, li), max(ld, rd)

        search(root)

        return length

    def doit_search_1(self, root: TreeNode) -> int:
        
        def calculate(node):
            if not node:
                return 0, 0

            inc, dec = 1, 1
            if node.left:
                l_inc, l_dec = calculate(node.left)
                if node.left.val == node.val - 1:
                    inc += l_inc
                elif node.left.val == node.val + 1:
                    dec += l_dec
            
            if node.right:
                r_inc, r_dec = calculate(node.right)
                if node.right.val == node.val - 1:
                    inc = max(r_inc+1, inc)
                elif node.right.val == node.val + 1:
                    dec = max(dec, 1+r_dec)
            
            res[0] = max(res[0], inc + dec - 1)
            
            return inc, dec
        
        res = [0]
        calculate(root)
        return res[0]









        