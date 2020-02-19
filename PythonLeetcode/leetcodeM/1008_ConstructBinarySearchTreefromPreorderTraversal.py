# 1008. Construct Binary Search Tree from Preorder Traversal

# Return the root node of a binary search tree that matches the given preorder traversal.

# (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val,
# and any descendant of node.right has a value > node.val.
# Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)


# Example 1:

# Input: [8,5,1,7,10,12]
# Output: [8,5,10,1,7,null,12]


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BstFromPreorder:

    def doit(self, preorder):
        """
        :type preorder: List[int]
        :rtype: TreeNode
        """
        root = TreeNode(preorder[0])
        st = [root]

        for i in range(1, len(preorder)):

            if not st:
                st.append(TreeNode(preorder[i]))

            elif st[-1].val > preorder[i]:
                st[-1].left = TreeNode(preorder[i])
                st.append(st[-1].left)

            elif st[-1].val < preorder[i]:

                while st and st[-1].val < preorder[i]:
                    last = st.pop()

                last.right = TreeNode(preorder[i])
                st.append(last.right)

        return root

    def doit(self, preorder):

        def dfs(i, j):
            if j < i:
                return None

            if i == j:
                return TreeNode(preorder[i])

            root = TreeNode(preorder[i])
            l = i+1

            while l <= j and preorder[l] < preorder[i]:
                l += 1

            root.left = dfs(i+1, l-1)
            root.right = dfs(l, j)

            return root

        return dfs(0, len(preorder)-1)


if __name__ == '__main__':

    res = BstFromPreorder().doit([8, 5, 1, 7, 10, 12])

    pass
