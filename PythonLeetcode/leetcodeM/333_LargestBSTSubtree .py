"""
333. Largest BST Subtree

Given the root of a binary tree, find the largest subtree, which is also a Binary Search Tree (BST), where the largest means subtree has the largest number of nodes.

A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned properties:

The left subtree values are less than the value of their parent (root) node's value.
The right subtree values are greater than the value of their parent (root) node's value.
Note: A subtree must include all of its descendants.

Follow up: Can you figure out ways to solve it with O(n) time complexity?



Example 1:



Input: root = [10,5,15,1,8,null,7]
Output: 3
Explanation: The Largest BST Subtree in this case is the highlighted one. The return value is the subtree's size, which is 3.
Example 2:

Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
Output: 2


Constraints:

The number of nodes in the tree is in the range [0, 104].
-104 <= Node.val <= 104


"""


# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class LargestBSTSubtree:

    def doit_search(self, root: TreeNode) -> int:

        def dfs(node):
            if not node:
                return 0, float('inf'), -float('inf')  # num, min, max

            left, lmin, lmax = dfs(node.left)
            right, rmin, rmax = dfs(node.right)

            if lmax < node.val < rmin:
                return left + 1 + right, min(lmin, node.val), max(rmax, node.val)

            return max(left, right), -float('inf'), float('inf')

        return dfs(root)[0]

    def doit_(self, root: 'TreeNode') -> int:

        if not root: return 0
        ans = 1

        def search(node):
            nonlocal ans
            if not node.left and not node.right:
                return True, 1, node.val, node.val

            bst, cnt, minv, maxv = True, 0, node.val, node.val

            if node.left:
                bstl, cntl, minl, maxl = search(node.left)

                if not bstl or node.val <= maxl:
                    bst = False

                if bst:
                    cnt += cntl
                    minv = min(minv, minl)
                    maxv = max(maxv, maxl)

            if node.right:
                bstr, cntr, minr, maxr = search(node.right)
                if not bstr or node.val >= minr:
                    bst = False
                if bst:
                    cnt += cntr
                    minv = min(minv, minr)
                    maxv = max(maxv, maxr)

            if not bst:
                return False, 0, 0, 0

            cnt += 1
            ans = max(ans, cnt)
            return True, cnt, minv, maxv

        search(root)
        return ans


if __name__ == '__main__':

    root = TreeNode(1)
    root.right = TreeNode(2)
    root.right.right = TreeNode(5)
    root.left = TreeNode(3)
    root.left.left = TreeNode(4)

    LargestBSTSubtree().doit_(root)