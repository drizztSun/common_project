# 1038. Binary Search Tree to Greater Sum Tree


# Given the root of a binary search tree with distinct values, modify it so that every node
# has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.

# As a reminder, a binary search tree is a tree that satisfies these constraints:

# The left subtree of a node contains only nodes with keys less than the node's key.
# The right subtree of a node contains only nodes with keys greater than the node's key.
# Both the left and right subtrees must also be binary search trees.


# Example 1:

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BstToGst:

    val = 0
    def bstToGst(self, root: TreeNode) -> TreeNode:
        if root.right:
            self.bstToGst(root.right)
        root.val = self.val = self.val + root.val
        if root.left:
            self.bstToGst(root.left)
        return root

    def doit(self, root):
        import heapq
        hpq, buff = [], [root]
        
        while buff:
            
            c = buff.pop()
            heapq.heappush(hpq, (-c.val, c))
            
            if c.left:
                buff.append(c.left)
            
            if c.right:
                buff.append(c.right)
                
        ans = 0
        while hpq:
            
            c = heapq.heappop(hpq)
            
            ans += -c[0]
            c[1].val = ans
            
        return root