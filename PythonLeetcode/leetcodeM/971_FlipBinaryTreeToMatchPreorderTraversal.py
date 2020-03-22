# 971. Flip Binary Tree To Match Preorder Traversal

# Given a binary tree with N nodes, each node has a different value from {1, ..., N}.

# A node in this binary tree can be flipped by swapping the left child and the right child of that node.

# Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.

# (Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)

# Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.

# If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.

# If we cannot do so, then return the list [-1].

# Definition for a binary tree node.


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class FlipMatchVoyage:

    """
    Approach 1: Depth-First Search
    Intuition

    As we do a pre-order traversal, we will flip nodes on the fly to try to match our voyage with the given one.

    If we are expecting the next integer in our voyage to be voyage[i], then there is only at most one choice for path to take, as all nodes have different values.

    Algorithm

    Do a depth first search. If at any node, the node's value doesn't match the voyage, the answer is [-1].

    Otherwise, we know when to flip: the next number we are expecting in the voyage voyage[i] is different from the next child.

    Complexity Analysis

    Time Complexity: O(N), where NN is the number of nodes in the given tree.

    Space Complexity: O(N).

    """

    def doit(self, root, voyage):

        self.ans = []
        self.index = 0

        def search(node):

            if not node:
                return

            if node.val != voyage[self.index]:
                self.ans = [-1]
                return

            self.index += 1
            if (
                self.index < len(voyage)
                and node.left
                and node.left.val != voyage[self.index]
            ):
                self.ans.append(node.val)
                search(node.right)
                search(node.left)
            else:
                search(node.left)
                search(node.right)

            return

        search(root)

        if self.ans and self.ans[0] == -1:
            self.ans = [-1]

        return self.ans


if __name__ == "__main__":

    root = TreeNode(1)
    root.left, root.right = TreeNode(2), TreeNode(3)

    res = FlipMatchVoyage().doit(root, [1, 3, 2])

    pass
