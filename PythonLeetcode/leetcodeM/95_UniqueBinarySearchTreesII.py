"""
95. Unique Binary Search Trees II

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class GenerateNumTrees:

    """
        Approach 1: Recursion
        First of all let's count how many trees do we have to construct. As you could check in this article, the number of possible BST is actually a Catalan number.

        Let's follow the logic from the above article, this time not to count but to actually construct the trees.

        Algorithm

        Let's pick up number i out of the sequence 1 ..n and use it as the root of the current tree. Then there are i - 1 elements available for the construction of the left subtree and n - i elements available for the right subtree. 
        As we already discussed that results in G(i - 1) different left subtrees and G(n - i) different right subtrees, where G is a Catalan number.

    """
    def generateTrees(self, n):
        """
        :type n: int
        :rtype: List[TreeNode]
        """
        def generate_trees(start, end):
            if start > end:
                return [None,]
            
            all_trees = []
            for i in range(start, end + 1):  # pick up a root
                # all possible left subtrees if i is choosen to be a root
                left_trees = generate_trees(start, i - 1)
                
                # all possible right subtrees if i is choosen to be a root
                right_trees = generate_trees(i + 1, end)
                
                # connect left and right subtrees to the root i
                for l in left_trees:
                    for r in right_trees:
                        current_tree = TreeNode(i)
                        current_tree.left = l
                        current_tree.right = r
                        all_trees.append(current_tree)
            
            return all_trees

        return generate_trees(1, n) if n else []

    def doit_dp(self, n: int) -> list[TreeNode]:
        """
        :type n: int
        :rtype: List[TreeNode]
        """
        def helper(start, end):
            if (start, end) in memo:
                return memo[start, end]

            tree = []
            for root in range(start, end + 1):

                left_list = helper(start, root - 1)
                right_list = helper(root + 1, end)

                for left in left_list:
                    for right in right_list:
                        node = TreeNode(root)
                        node.left = left
                        node.right = right
                        tree.append(node)

            memo[start, end] = tree or [None]
            return tree or [None]

        memo = {}
        if n == 0:
            return []
        return helper(1, n)

    def doit_divide_conquer(self, n: int) -> list[TreeNode]:
        # divide and conquer
        def rec(start, end):
            curr_res = []
            if start > end:
                curr_res.append(None)
                return curr_res
            # if start == end:
            #     curr_res.append(TreeNode(start))
            #     return curr_res

            for i in range(start, end + 1):
                left = rec(start, i - 1)
                right = rec(i + 1, end)

                for l in left:
                    for r in right:
                        n = TreeNode(i, l, r)
                        curr_res.append(n)
            return curr_res

        if n == 0: return []

        return rec(1, n)