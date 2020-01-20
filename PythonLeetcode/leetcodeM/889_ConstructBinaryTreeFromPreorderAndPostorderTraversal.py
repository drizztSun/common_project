# 889. Construct Binary Tree from Preorder and Postorder Traversal

# Return any binary tree that matches the given preorder and postorder traversals.

# Values in the traversals pre and post are distinct positive integers.


# Example 1:

# Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
# Output: [1,2,3,4,5,6,7]


# Note:

# 1 <= pre.length == post.length <= 30
# pre[] and post[] are both permutations of 1, 2, ..., pre.length.
# It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class ConstructFromPrePost:

    """
    Approach 1: Recursion
    Intuition

    A preorder traversal is:

    (root node) (preorder of left branch) (preorder of right branch)
    While a postorder traversal is:

    (postorder of left branch) (postorder of right branch) (root node)
    For example, if the final binary tree is [1, 2, 3, 4, 5, 6, 7] (serialized), then the preorder traversal is [1] + [2, 4, 5] + [3, 6, 7], while the postorder traversal is [4, 5, 2] + [6, 7, 3] + [1].

    If we knew how many nodes the left branch had, we could partition these arrays as such, and use recursion to generate each branch of the tree.

    Algorithm

    Let's say the left branch has LL nodes. We know the head node of that left branch is pre[1], but it also occurs last in the postorder representation of the left branch. So pre[1] = post[L-1] (because of uniqueness of the node values.) Hence, L = post.indexOf(pre[1]) + 1.

    Now in our recursion step, the left branch is represnted by pre[1 : L+1] and post[0 : L], while the right branch is represented by pre[L+1 : N] and post[L : N-1].

    Complexity Analysis

    Time Complexity: O(N^2), where NN is the number of nodes.

    Space Complexity: O(N^2).

    """

    def doit(self, pre, post):

        def build_tree(pre_ord, post_ord):

            if len(pre_ord) == 0:
                return None

            root = TreeNode(pre_ord[0])

            if len(pre_ord) > 1:

                l = post_ord.index(pre_ord[1])

                root.left = build_tree(pre_ord[1:1+l+1], post_ord[:l+1])

                root.right = build_tree(pre_ord[1+l+1:], post_ord[l+1:-1])

            return root

        return build_tree(pre, post)

    """
    Approach 2: Recursion (Space Saving Variant)
    Explanation

    We present a variation of Approach 1 that uses indexes to refer to the subarrays of pre and post, instead of passing copies of those subarrays. Here, (i0, i1, N) refers to pre[i0:i0+N], post[i1:i1+N].
    """
    def doit(self, pre, post):
        def make(i0, i1, N):
            if N == 0:
                return None
            root = TreeNode(pre[i0])
            if N == 1:
                return root

            for L in range(N):
                if post[i1 + L - 1] == pre[i0 + 1]:
                    break

            root.left = make(i0 + 1, i1, L)
            root.right = make(i0 + L + 1, i1 + L, N - 1 - L)
            return root

        return make(0, 0, len(pre))


if __name__ == '__main__':

    res = ConstructFromPrePost().doit(
        pre=[1, 2, 4, 5, 3, 6, 7], post=[4, 5, 2, 6, 7, 3, 1])

    res = ConstructFromPrePost().doit([2, 1], [1, 2])

    pass
