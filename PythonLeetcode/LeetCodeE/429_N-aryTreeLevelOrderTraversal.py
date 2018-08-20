# 429. N-ary Tree Level Order Traversal


# Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

# For example, given a 3-ary tree:

 


 
# We should return its level order traversal:


# [
#      [1],
#      [3,2,4],
#      [5,6]
# ]



# Definition for a Node.
class Node(object):
    def __init__(self, val, children):
        self.val = val
        self.children = children

class NAryInlevelOrder(object):
    def doit(self, root):
        """
        :type root: Node
        :rtype: List[List[int]]
        """
        if not root:
            return []

        buff = [root]
        res = []

        while buff:

            newbuff = []
            res.append([])

            for c in buff:
                res[-1].append(c.val)
                
                for s in c.children:
                    newbuff.append(s)

            buff = newbuff 

        return res


if __name__ == "__main__":

    pass