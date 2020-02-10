# 987. Vertical Order Traversal of a Binary Tree

# Given a binary tree, return the vertical order traversal of its nodes values.

# For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

# Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

# If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

# Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.


# Example 1:

# Input: [3,9,20,null,null,15,7]
# Output: [[9],[3,15],[20],[7]]
# Explanation:
# Without loss of generality, we can assume the root node is at position (0, 0):
# Then, the node with value 9 occurs at position (-1, -1);
# The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
# The node with value 20 occurs at position (1, -1);
# The node with value 7 occurs at position (2, -2).

# Example 2:

# Input: [1,2,3,4,5,6,7]
# Output: [[4],[2],[1,5,6],[3],[7]]
# Explanation:
# The node with value 5 and the node with value 6 have the same position according to the given scheme.
# However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.

# Definition for a binary tree node.
import collections


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class VerticalTraversal:

    def doit(self, root):

        seen = collections.defaultdict(lambda: collections.defaultdict(list))

        def depth(node, x, y):
            if not node:
                return

            seen[x][y].append(node.val)

            depth(node.left, x-1, y+1)
            depth(node.right, x+1, y+1)

        depth(root, 0, 0)

        ans = []
        for x in sorted(seen):
            report = []
            for y in sorted(seen[x]):
                report.extend(sorted(c for c in sorted(seen[x][y])))

            ans.append(report)

        return ans

    def doit(self, root):

        travels = {}
        buff = [(root, 0, 0)]

        while buff:

            buff2 = []

            while buff:
                c, x, y = buff.pop()

                if x not in travels:
                    travels[x] = []

                travels[x].append((c.val, y))

                if c.left:
                    buff2.append((c.left, x-1, y-1))

                if c.right:
                    buff2.append((c.right, x+1, y-1))

            buff = buff2

        ans = []
        for k in sorted(travels.keys()):
            ans.append([x[0] for x in sorted(
                travels[k], key=lambda x: (-x[1], x[0]))])

        return ans


if __name__ == '__main__':

    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    # [3,9,20,null,null,15,7]
    res = VerticalTraversal().doit(root)

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)

    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)

    root.right.left = TreeNode(6)
    root.right.right = TreeNode(7)

    res = VerticalTraversal().doit(root)

    # [0,2,1,3,null,null,null,4,5,null,7,6,null,10,8,11,9]
    # [[4,10,11],[3,6,7],[2,5,8,9],[0],[1]]

    root = TreeNode(0)
    root.left = TreeNode(5)
    root.right = TreeNode(1)

    root.left.left = TreeNode(9)

    root.right.left = 2

    pass
