# 623. Add One Row to Tree

# Given the root of a binary tree, then value v and depth d, you need to add a row of nodes with value v at the given depth d.
# The root node is at depth 1.

# The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1, 
# create two tree nodes with value v as N's left subtree root and right subtree root. 
# And N's original left subtree should be the left subtree of the new left subtree root, 
# its original right subtree should be the right subtree of the new right subtree root.
# 
#  If depth d is 1 that means there is no depth d-1 at all, 
#  then create a tree node with value v as the new root of the whole original tree,
#  and the original tree is the new root's left subtree.

#Example 1:
#Input: 
#A binary tree as following:
#       4
#     /   \
#    2     6
#   / \   / 
#  3   1 5   

#v = 1

#d = 2

#Output: 
#       4
#      / \
#     1   1
#    /     \
#   2       6
#  / \     / 
# 3   1   5   

#Example 2:
#Input: 
#A binary tree as following:
#      4
#     /   
#    2    
#   / \   
#  3   1    

#v = 1

#d = 3

#Output: 
#      4
#     /   
#    2
#   / \    
#  1   1
# /     \  
#3       1
#Note:
#The given d is in range [1, maximum depth of the given tree + 1].
#The given binary tree has at least one tree node.


class TreeNode:

    def __init__(self, v):
        self.val = v
        self.left, self.right = None, None

class AddOneRow:


    def doit(self, root, v, d):
        """
        :type root: TreeNode
        :type v: int
        :type d: int
        :rtype: TreeNode
        """
        nodes = [root]
        if d == 1:
            node = TreeNode(v)
            node.left = root
            return node

        for i in range(1, d-1):
            temp = []
            for node in nodes:
                if node.left:
                    temp.append(node.left)
                if node.right:
                    temp.append(node.right)
            nodes = temp

        for node in nodes:
            temp = node.left
            node.left = TreeNode(v)
            node.left.left = temp
            temp = node.right
            node.right = TreeNode(v)
            node.right.right = temp

        return root


    def doit1(self, root, v, d):
        """
        :type root: TreeNode
        :type v: int
        :type d: int
        :rtype: TreeNode
        """
        if d == 1:
            s = TreeNode(v)
            s.left = root
            return s

        buff, depth = [root], 1

        while buff and depth < d:
            if depth == d - 1:
                
                for c in buff:
                    if c.left:
                        s = TreeNode(v)
                        c.left, s.left = s, c.left

                    if c.right:
                        s = TreeNode(v)
                        c.right, s.right = s, c.right
                depth += 1
                
            else:
                depth += 1
                newbuff = []
                for c in buff:
                    if c.left:
                        newbuff.append(c.left)
                    if c.right:
                        newbuff.append(c.right)

                buff = newbuff

        return root


if __name__ == "__main__":

    root = TreeNode(1)
    root.left, root.right = TreeNode(2), TreeNode(3)
    root.left.left = TreeNode(4)

    res = AddOneRow().doit(root, 5, 4)