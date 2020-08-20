
# 94. Binary Tree Inorder Traversal

# Given a binary tree, return the inorder traversal of its nodes' values.

# Example:

# Input: [1,null,2,3]
#    1
#     \
#      2
#     /
#    3

# Output: [1,3,2]
# Follow up: Recursive solution is trivial, could you do it iteratively?


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class InorderTraversal(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """

        node, res, buff = root, [], []

        while node or buff:
            if node:
                buff.append(node)
                node = node.left

            else:
                n = buff.pop()
                res.append(n.val)
                node = n.right

        return res

    def doit(self, root):
        cur, buff, res = root, [], []
        while cur:
            if cur.left:
                buff.append(cur)
                cur = cur.left
                continue

            res.append(cur.val)
            while not cur.right and buff:
                cur = buff.pop()
                res.append(cur.val)
            cur = cur.right

        return res


if __name__ == "__main__":

    root = TreeNode(1)
    root.right = TreeNode(2)
    root.right.left = TreeNode(3)

    res = InorderTraversal().doit(root)
