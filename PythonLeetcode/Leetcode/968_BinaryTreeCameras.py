#  968. Binary Tree Cameras

# Given a binary tree, we install cameras on the nodes of the tree.

# Each camera at a node can monitor its parent, itself, and its immediate children.

# Calculate the minimum number of cameras needed to monitor all nodes of the tree.


class BinaryTreeCamera:

    """
    Approach 1: Dynamic Programming
    Intuition

    Let's try to cover every node, starting from the top of the tree and working down. Every node considered must be covered by a camera at that node or some neighbor.

    Because cameras only care about local state, we can hope to leverage this fact for an efficient solution.
    Specifically, when deciding to place a camera at a node, we might have placed cameras to cover some subset of this node, its left child, and its right child already.

    Algorithm

    Let solve(node) be some information about how many cameras it takes to cover the subtree at this node in various states. There are essentially 3 states:

    [State 0] Strict subtree: All the nodes below this node are covered, but not this node.
    [State 1] Normal subtree: All the nodes below and including this node are covered, but there is no camera here.
    [State 2] Placed camera: All the nodes below and including this node are covered, and there is a camera here (which may cover nodes above this node).
    Once we frame the problem in this way, the answer falls out:

    To cover a strict subtree, the children of this node must be in state 1.
    To cover a normal subtree without placing a camera here, the children of this node must be in states 1 or 2, and at least one of those children must be in state 2.
    To cover the subtree when placing a camera here, the children can be in any state.
    """

    def doit(self, root):
        def search(node):

            if not node:
                return 0, 0, float("inf")

            l = search(node.left)
            r = search(node.right)

            ans1 = l[1] + r[1]
            ans2 = min(l[2] + min(r[1:]), r[2] + min(l[1:]))
            ans3 = min(min(l), min(r))

            return ans1, ans2, ans3

        return min(search(root)[1:])

    """
    Approach 2: Greedy
    Intuition

    Instead of trying to cover every node from the top down,
    let's try to cover it from the bottom up - considering placing a camera with the deepest nodes first, and working our way up the tree.

    If a node has its children covered and has a parent, then it is strictly better to place the camera at this node's parent.

    Algorithm

    If a node has children that are not covered by a camera, then we must place a camera here.
    Additionally, if a node has no parent and it is not covered, we must place a camera here.

    Complexity Analysis

    Time Complexity: O(N), where N is the number of nodes in the given tree.

    Space Complexity: O(H), where H is the height of the given tree.
    """

    def doit1(self, root):
        self.ans = 0
        covered = {None}

        def dfs(node, par=None):
            if node:
                dfs(node.left, node)
                dfs(node.right, node)

                if (
                    par is None
                    and node not in covered
                    or node.left not in covered
                    or node.right not in covered
                ):
                    self.ans += 1
                    covered.update({node, par, node.left, node.right})

        dfs(root)
        return self.ans
