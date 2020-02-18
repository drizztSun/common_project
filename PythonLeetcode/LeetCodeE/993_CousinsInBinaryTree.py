# 993. Cousins in Binary Tree

# In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

# Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

# We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

# Return true if and only if the nodes corresponding to the values x and y are cousins.


# Example 1:

# Input: root = [1,2,3,4], x = 4, y = 3
# Output: false

# Example 2:

# Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
# Output: true

# Example 3:

# Input: root = [1,2,3,null,4], x = 2, y = 3
# Output: false

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class IsCousins:

    def doit(self, root, x, y):

        st = [(root, None, 0)]

        xp, xd, yp, yd = None, 0, None, 0

        while st:

            c, p, d = st.pop()

            if c.val == x:
                xp, xd = p, d
            elif c.val == y:
                yp, yd = p, d

            if c.left:
                st.append((c.left, c, d+1))

            if c.right:
                st.append((c.right, c, d + 1))

        return xd == yd and xp != yp

    """
    Approach 1: Annotate Parent and Depth
    Intuition
    Nodes are cousins if they have the same depth but different parents. A straightforward approach is to be able to know the parent and depth of each node.

    Algorithm
    We can use a depth-first search to annotate each node. For each node with parent par and depth d, we will record results in hashmaps: parent[node.val] = par and depth[node.val] = d.

    Complexity Analysis

    Time Complexity: O(N), where NN is the number of nodes in the tree.
    Space Complexity: O(N).
    """

    def doit(self, root, x, y):

        parent = {}
        depth = {}

        def dfs(node, par=None):
            if node:
                depth[node.val] = 1 + depth[par.val] if par else 0
                parent[node.val] = par
                dfs(node.left, node)
                dfs(node.right, node)

        dfs(root)
        return depth[x] == depth[y] and parent[x] != parent[y]


if __name__ == '__main__':

    r = TreeNode(1)
    r.left = TreeNode(2)
    r.right = TreeNode(3)
    r.left.left = TreeNode(4)

    res = IsCousins().doit(r, x=4, y=3)

    r = TreeNode(1)
    r.left = TreeNode(2)
    r.right = TreeNode(3)
    r.left.left = TreeNode(4)
    r.right.right = TreeNode(5)

    res = IsCousins().doit(r, x=5, y=4)

    r = TreeNode(1)
    r.left = TreeNode(2)
    r.right = TreeNode(3)
    r.left.right = TreeNode(4)

    res = IsCousins().doit(r, x=2, y=3)

    pass
