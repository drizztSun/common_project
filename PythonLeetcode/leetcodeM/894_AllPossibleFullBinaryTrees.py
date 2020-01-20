# 894. All Possible Full Binary Trees

# A full binary tree is a binary tree where each node has exactly 0 or 2 children.

# Return a list of all possible full binary trees with N nodes.
# Each element of the answer is the root node of one possible tree.

# Each node of each tree in the answer must have node.val = 0.

# You may return the final list of trees in any order.


# Example 1:

# Input: 7
# Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
# Explanation:


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:

    def __init__(self):

        self.full_bst = dict()

        # base case of full binary tree with one node
        self.full_bst[1] = [TreeNode(0)]

    def allPossibleFBT(self, N):

        if N % 2 == 0:
            # if N is even number, there is no chance to build full binary tree
            return []

        if N in self.full_bst:
            # if Full BST with N is constructed before, then reutrn by look-up dictionary
            return self.full_bst[N]

        else:
            # Construct Full BST with N Nodes by top-down recursion with memorization

            # a list to store different BST with N Nodes
            tree = []

            # total n nodes:
            # 1 for root node
            # left_subtree_nodes for left-sub-full-bst
            # n-1-left_subtree_nodes for right-sub-full-bst
            for left_subtree_nodes in range(1, N, +2):

                # Divide-and-conquer
                left_sub_trees = self.allPossibleFBT(left_subtree_nodes)
                right_sub_trees = self.allPossibleFBT(
                    (N-1) - left_subtree_nodes)

                # Construct Full BST with all possible combination of left-sub-full-bst and right-sub-full-bst
                for left_subt in left_sub_trees:
                    for right_subt in right_sub_trees:

                        root = TreeNode(0)
                        root.left = left_subt
                        root.right = right_subt

                        tree.append(root)

            self.full_bst[N] = tree
            return tree


class AllPossibleFBT:

    def doit(self, N):

        memo = {0: [], 1: [TreeNode(0)]}

        def build_tree(n):
            if n in memo:
                return memo[n]

            ans = []
            for i in range(1, n, 2):
                lefts = build_tree(i)
                rights = build_tree(n - i - 1)

                for l in lefts:
                    for r in rights:
                        r = TreeNode(0)
                        r.left = l
                        r.right = r
                        ans.append(r)
            memo[n] = ans
            return ans

        build_tree(N)
        return memo[N]


if __name__ == '__main__':

    res = AllPossibleFBT().doit(7)

    res = Solution().allPossibleFBT(7)

    pass
