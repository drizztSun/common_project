import os
import collections


# 297 Serialzie and Deserialize Binary Tree

# Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

# Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

# For example, you may serialize the following tree

#    1
#   / \
#  2   3
#     / \
#    4   5
# as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec1:

    def serialize(self, root):
        def doit(node):
            if node:
                vals.append(str(node.val))
                doit(node.left)
                doit(node.right)
            else:
                vals.append('#')
        vals = []
        doit(root)
        return ','.join(vals)

    def deserialize(self, data):
        def doit():
            val = next(vals)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left = doit()
            node.right = doit()
            return node
        vals = iter(data.split(','))
        return doit()


# BFS
class CodecBFS:

    def serialize(self, root):
        """
        Encodes a tree to a single string.
        :type root: TreeNode
        :rtype: str
        """
        buff = collections.deque()
        res = []
        buff.append(root)

        while buff:

            tmp = collections.deque()
            while buff:
                a = buff.popleft()
                res.append(str(a.val) if a else "N")

                if a:
                    tmp.append(a.left)
                    tmp.append(a.right)

            if any(tmp):
                buff = tmp

        return ' '.join(res)

    def deserialize(self, data1):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data1:
            return None

        data = data1.split()
        root = TreeNode(int(data[0])) if data[0] != 'N' else None
        pt = collections.deque()
        pt.append(root)

        i, step = 1, 2
        while i < len(data):

            tmp = collections.deque()
            valid = 0
            while step > 0:

                t = pt.popleft()
                t.left = TreeNode(int(data[i])) if data[i] != 'N' else None
                t.right = TreeNode(
                    int(data[i+1])) if data[i+1] != 'N' else None

                if t.left:
                    tmp.append(t.left)

                if t.right:
                    tmp.append(t.right)

                i += 2
                step -= 2

            step = len(tmp) * 2
            pt = tmp

        return root


# DFS Preorder Recursion
class CodecReCursivePreOrder:

    def serialize(self, root):
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        def doit(node):
            if not node:
                return '#'

            res = str(node.val)
            res += ' ' + doit(node.left)
            res += ' ' + doit(node.right)

            return res

        return doit(root)

    def deserialize(self, data1):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data1:
            return None

        data = data1.split()
        content = iter(data)

        def doit(pt):

            val = next(pt)
            if val == '#':
                return None

            node = TreeNode(int(val))

            node.left = doit(pt)

            node.right = doit(pt)

            return node

        return doit(content)


if __name__ == "__main__":

    # Your Codec object will be instantiated and called as such:

    codec = CodecReCursivePreOrder()

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.right.left = TreeNode(4)
    root.right.right = TreeNode(5)

    res = codec.deserialize(codec.serialize(root))

    root = TreeNode(-1)
    root.left = TreeNode(0)
    root.right = TreeNode(1)

    res = codec.deserialize(codec.serialize(root))

    pass
