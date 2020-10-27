"""
106. Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7


"""


class BuildTreeWithInorderAndPostorder:

    # Definition for a binary tree node.
    class TreeNode:
        def __init__(self, val=0, left=None, right=None):
            self.val = val
            self.left = left
            self.right = right

    def doit(self, inorder, postorder):

        def helper(in_left, in_right):
            # if there is no elements to construct subtrees
            if in_left > in_right:
                return None

            # pick up the last element as a root
            val = postorder.pop()
            root = BuildTreeWithInorderAndPostorder.TreeNode(val)

            # root splits inorder list
            # into left and right subtrees
            index = idx_map[val]

            # build right subtree
            root.right = helper(index + 1, in_right)
            # build left subtree
            root.left = helper(in_left, index - 1)
            return root

        # build a hashmap value -> its index
        idx_map = {val: idx for idx, val in enumerate(inorder)}
        return helper(0, len(inorder) - 1)

    def doit(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: TreeNode
        """
        def buildTree(inorder, postorder):
            if not inorder:
                return None

            val = postorder[len(postorder)-1]
            i, root = 0, BuildTreeWithInorderAndPostorder.TreeNode(val)
            if len(inorder) == 1:
                return root

            while i < len(inorder):
                if inorder[i] == val:
                    break
                i += 1

            root.left = buildTree(inorder[0:i], postorder[0:i])
            root.right = buildTree(inorder[i+1:], postorder[i:len(postorder)-1])

            return root

        return buildTree(inorder, postorder)

if __name__ == '__main__':

    BuildTreeWithInorderAndPostorder().doit(inorder = [9,3,15,20,7], postorder = [9,15,7,20,3])