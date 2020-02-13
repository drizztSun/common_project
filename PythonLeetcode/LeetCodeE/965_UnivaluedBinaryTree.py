# 965. Univalued Binary Tree

# A binary tree is univalued if every node in the tree has the same value.

# Return true if and only if the given tree is univalued.

# Definition for a binary tree node.


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class IsUnivalTree:

    """
    Approach 1: Depth-First Search
    Intuition and Algorithm

    Let's output all the values of the array. After, we can check that they are all equal.

    To output all the values of the array, we perform a depth-first search.
    Complexity Analysis

    Time Complexity: O(N)O(N), where NN is the number of nodes in the given tree.

    Space Complexity: O(N)O(N).
    """

    def doit(self, root):
        vals = []

        def dfs(node):
            if node:
                vals.append(node.val)
                dfs(node.left)
                dfs(node.right)

        dfs(root)
        return len(set(vals)) == 1

    """
    Approach 2: Recursion
    Intuition and Algorithm

    A tree is univalued if both its children are univalued, plus the root node has the same value as the child nodes.

    We can write our function recursively. left_correct will represent that the left child is correct: ie.,
    that it is univalued, and the root value is equal to the left child's value.
    right_correct will represent the same thing for the right child. We need both of these properties to be true.

    Complexity Analysis

    Time Complexity: O(N)O(N), where NN is the number of nodes in the given tree.

    Space Complexity: O(H)O(H), where HH is the height of the given tree.
    """

    def isUnivalTree(self, root):

        def search(node):
            left_correct = (not node.left or node.val == node.left.val
                            and search(root.left))
            right_correct = (not node.right or node.val == node.right.val
                             and search(root.right))
            return left_correct and right_correct

        return search(root)

    def doit(self, root):

        buff = [root]
        ans = None

        while buff:

            c = buff.pop()

            if ans == None:
                ans = c.val
            elif ans != c.val:
                return False

            if c.left:
                buff.append(c.left)
            if c.right:
                buff.append(c.right)

        return True


if __name__ == '__main__':

    root = TreeNode(1)
    root.left = TreeNode(1)
    root.left.left = TreeNode(1)
    root.left.right = TreeNode(1)
    root.right = TreeNode(1)
    root.right.right = TreeNode(1)

    res = IsUnivalTree().doit(root)

    pass
