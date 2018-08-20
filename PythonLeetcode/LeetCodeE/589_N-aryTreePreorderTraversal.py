# 589. N-ary Tree Preorder Traversal

# Given an n-ary tree, return the preorder traversal of its nodes' values.
# For example, given a 3-ary tree:
# Return its preorder traversal as: [1,3,5,6,2,4].


# Definition for a Node.
class Node(object):
    def __init__(self, val, children):

        self.val = val
        self.children = children

class PreorderInNAryTree(object):

    def doit(self, root):
        """
        :type root: Node
        :rtype: List[int]
        """
        if not root:
            return []
            
        buff, res = [root], []

        while buff:

            n = buff.pop()

            res.append(n.val)

            for c in reversed(n.children):
                buff.append(c)

        return res


if __name__ == "__main__":

    pass