"""
105. Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7


"""


class BuildTreeWithInorderAndPreorder:


    # Definition for a binary tree node.
    class TreeNode:
        def __init__(self, val=0, left=None, right=None):
            self.val = val
            self.left = left
            self.right = right

    def doit_(self, preorder, inorder):

        def build(preorder, inorder):

            if not preorder:
                return None

            root = BuildTreeWithInorderAndPreorder.TreeNode(preorder[0])

            i = 0
            while i < len(inorder) and inorder[i] != preorder[0]:
                i += 1

            root.left = build(preorder[1:i + 1], inorder[:i])
            root.right = build(preorder[i + 1:], inorder[i + 1:])

            return root

        return build(preorder, inorder)

    """
    Approach 1: Recursion
    Tree definition

    First of all, here is the definition of the TreeNode which we would use.

    Algorithm

    As discussed above the preorder traversal follows Root -> Left -> Right order, that makes it very convenient to construct the tree from its root.

    Let's do it. The first element in the preorder list is a root. This root splits inorder list into left and right subtrees.
    Now one have to pop up the root from preorder list since it's already used as a tree node and then repeat the step above for the left and right subtrees.

    """
    def doit(self, preorder, inorder):

        def helper(in_left=0, in_right=len(inorder)):
            nonlocal pre_idx
            # if there is no elements to construct subtrees
            if in_left == in_right:
                return None

            # pick up pre_idx element as a root
            root_val = preorder[pre_idx]
            root = BuildTreeWithInorderAndPreorder.TreeNode(root_val)

            # root splits inorder list
            # into left and right subtrees
            index = idx_map[root_val]

            # recursion
            pre_idx += 1
            # build left subtree
            root.left = helper(in_left, index)
            # build right subtree
            root.right = helper(index + 1, in_right)
            return root

        # start from first preorder element
        pre_idx = 0
        # build a hashmap value -> its index
        idx_map = {val: idx for idx, val in enumerate(inorder)}
        return helper()

    def doit(self, preorder, inorder):

        def helper(in_left, in_right):

            if in_left > in_right:
                return None

            # pick up pre_idx element as a root
            root_val = preorder.pop(0)
            root = BuildTreeWithInorderAndPreorder.TreeNode(root_val)

            # root splits inorder list
            # into left and right subtrees
            index = idx_map[root_val]

            root.left = helper(in_left, index-1)

            root.right = helper(index + 1, in_right)
            return root

        idx_map = {val: idx for idx, val in enumerate(inorder)}
        return helper(0, len(inorder)-1)


if __name__ == '__main__':

    BuildTreeWithInorderAndPreorder().doit(preorder=[3,9,20,15,7], inorder=[9,3,15,20,7])