# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def levelOrderBottom(self, root: TreeNode):
        if not root:
            return []
        c = [root]
        res = []
        while c:
            n = []
            for i in c:
                if i.left:
                    n.append(i.left)
                if i.right:
                    n.append(i.right)
            res.append([j.val for j in c])
            c = n
        return res[::-1]


if __name__ == '__main__':
    a = TreeNode(3, TreeNode(9, None, None), TreeNode(20, TreeNode(15, None, None), TreeNode(7, None, None)))
    print(Solution().levelOrderBottom(a))
