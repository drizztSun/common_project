"""
1373. Maximum Sum BST in Binary Tree


Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:



Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
Output: 20
Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
Example 2:



Input: root = [4,3,null,1,2]
Output: 2
Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.
Example 3:

Input: root = [-4,-2,-5]
Output: 0
Explanation: All values are negatives. Return an empty BST.
Example 4:

Input: root = [2,1,3]
Output: 6
Example 5:

Input: root = [5,4,8,3,null,6,3]
Output: 7


Constraints:

The given binary tree will have between 1 and 40000 nodes.
Each node's value is between [-4 * 10^4 , 4 * 10^4].

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class MaxSumBST:

    def doit_BST(self, root):

        res = 0

        def search(node):
            nonlocal res

            if not node:
                return (1e9, -1e9, 0, True)

            lmin, lmax, lv, lb = search(node.left)
            rmin, rmax, rv, rb = search(node.right)

            b = lb and rb and node.val > lmax and node.val < rmin
            v = -1 if not b else (lv + rv + node.val)
            res = max(res, v)
            return min(lmin, rmin, node.val), max(lmax, rmax, node.val), v, b

        search(root)
        return res

    def doit_BST_1(self, root) -> int:
        max_sum = 0

        def is_bst(root) -> tuple:
            is_tree_bst, min_node, max_node, tree_sum = True, root.val, root.val, root.val
            if root.left:
                left_bst = is_bst(root.left)
                if left_bst and root.val > left_bst[1]:
                    min_node = left_bst[0]
                    tree_sum += left_bst[2]
                else:
                    is_tree_bst = False
            if root.right:
                right_bst = is_bst(root.right)
                if right_bst and root.val < right_bst[0]:
                    max_node = right_bst[1]
                    tree_sum += right_bst[2]
                else:
                    is_tree_bst = False

            if is_tree_bst:
                nonlocal max_sum
                max_sum = max(max_sum, tree_sum)
                return min_node, max_node, tree_sum

        is_bst(root)
        return max_sum
