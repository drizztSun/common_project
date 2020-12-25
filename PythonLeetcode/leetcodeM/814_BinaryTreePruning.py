"""
814. Binary Tree Pruning


We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class PruneTree:


    """
    Approach #1: Recursion [Accepted]
    Intuition

    Prune children of the tree recursively. The only decisions at each node are whether to prune the left child or the right child.

    Algorithm

    We'll use a function containsOne(node) that does two things: it tells us whether the subtree at this node contains a 1, and it also prunes all subtrees not containing 1.

    If for example, node.left does not contain a one, then we should prune it via node.left = null.

    Also, the parent needs to be checked. If for example the tree is a single node 0, the answer is an empty tree.

    Complexity Analysis

    Time Complexity: O(N)O(N), where NN is the number of nodes in the tree. We process each node once.

    Space Complexity: O(H)O(H), where HH is the height of the tree. This represents the size of the implicit call stack in our recursion.
    """
    def doit_recursive(self, root):
        def containsOne(node):
            if not node: return False
            a1 = containsOne(node.left)
            a2 = containsOne(node.right)
            if not a1: node.left = None
            if not a2: node.right = None
            return node.val == 1 or a1 or a2

        return root if containsOne(root) else None

    def doit(self, root):

        def dfs(node):

            if not node.left and not node.right:
                return node.val == 0

            left = True if not node.left else dfs(node.left)
            right = True if not node.right else dfs(node.right)

            if left:
                node.left = None
            if right:
                node.right = None

            return left and right and node.val == 0

        dfs(root)

    def doit1(self, root):

        def recur(n):

            if not n:
                return True

            l, r = not n.left or recur(n.left), not n.right or recur(n.right)

            if l:
                n.left = None
            if r:
                n.right = None

            return l and r and n.val == 0

        return None if recur(root) else root