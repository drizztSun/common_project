"""
101. Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3


But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3


Follow up: Solve it both recursively and iteratively.

"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class IsSymmetric:

    def doit_(self, root: TreeNode) -> bool:

        def check_symmetric(n1, n2):
            if not n1 or not n2:
                return n1 == n2

            return n1.val == n2.val and check_symmetric(n1.left, n2.right) and check_symmetric(n1.right, n2.left)

        return check_symmetric(root.left, root.right)

    def doit_2(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        def check(rootA, rootB):
            if rootA == rootB == None:
                return True

            if rootA == None or rootB == None or rootA.val != rootB.val:
                return False

            return check(rootA.right, rootB.left) and check(rootA.left, rootB.right)

        if root == None:
            return True
        return check(root.left, root.right)

if __name__ == '__main__':

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(2)

    root.left.left = TreeNode(3)
    root.left.right = TreeNode(4)

    root.right.left = TreeNode(4)
    root.right.right = TreeNode(3)

    IsSymmetric().doit_(root)