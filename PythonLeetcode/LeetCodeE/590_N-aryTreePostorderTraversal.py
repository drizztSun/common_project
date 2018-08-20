# 590. N-ary Tree Postorder Traversal

# Given an n-ary tree, return the postorder traversal of its nodes' values.
# For example, given a 3-ary tree:
# Return its postorder traversal as: [5,6,3,2,4,1].



# Definition for a Node.
class Node(object):
    def __init__(self, val, children):
        self.val = val
        self.children = children

class PostorderInNAryTree(object):
    def postorder(self, root):
        """
        :type root: Node
        :rtype: List[int]
        """
        from collections import deque as dq
        if not root:
            return []

        buff, res = [root], dq()
        
        while buff:

            n = buff.pop()
            res.appendleft(n.val)

            for c in n.children:
                buff.append(c)

        return list(res)



if __name__ == "__main__":

    pass
 