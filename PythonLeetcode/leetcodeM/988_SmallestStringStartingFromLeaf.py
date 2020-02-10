# 988. Smallest String Starting From Leaf

# Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z':
# a value of 0 represents 'a', a value of 1 represents 'b', and so on.

# Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

# (As a reminder, any shorter prefix of a string is lexicographically smaller:
# for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)


# Definition for a binary tree node.

# Example 1:
# Input: [0,1,2,3,4,3,4]
# Output: "dba"

# Example 2:
# Input: [25,1,3,1,3,0,2]
# Output: "adz"

# Example 3:
# Input: [2,2,1,null,1,0,null,0]
# Output: "abc"

from functools import lru_cache


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class SmallestFromLeaf:

    def doit(self, root):

        self._ans = None
        base = 'abcdefghijklmnopqrstuvwxyz'

        def search(n, path):

            if not n.left and not n.right:

                r = ''.join([base[n.val]] + path)
                if not self._ans or self._ans > r:
                    self._ans = r
                return

            if n.left:
                search(n.left, [base[n.val]] + path)

            if n.right:
                search(n.right, [base[n.val]] + path)

        search(root, [])

        return self._ans

    def doit(self, root):

        cache = OrderedDict()
        self.traverse(root, 0, 0, cache)
        return [[val[0] for val in sorted(item[1], key=lambda x: (abs(x[1]), x[0]))] for item in sorted(cache.items(), key=lambda x: x[0])]

    def traverse(self, root, x, y, cache):
        if not root:
            return
        else:

            self.traverse(root.left, x - 1, y - 1, cache)

            curr = cache.get(x, [])
            curr.append((root.val, y))
            cache[x] = curr
            self.traverse(root.right, x + 1, y - 1, cache)


if __name__ == '__main__':

    root = TreeNode(0)
    root.left = TreeNode(1)
    root.right = TreeNode(2)

    root.left.left = TreeNode(3)
    root.left.right = TreeNode(4)

    root.right.left = TreeNode(3)
    root.right.right = TreeNode(4)

    res = SmallestFromLeaf().doit(root)

    # [23,13,7,19,16]

    root = TreeNode(23)
    root.right = TreeNode(7)
    root.left = TreeNode(13)

    root.left.left = TreeNode(19)
    root.left.right = TreeNode(16)

    res = SmallestFromLeaf().doit(root)  # "hx"

    pass
