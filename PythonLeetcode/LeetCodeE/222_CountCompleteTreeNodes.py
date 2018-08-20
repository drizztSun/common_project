import os


# leetcode 222. Count Complete Tree Nodes

# Given a complete binary tree, count the number of nodes.
# Definition of a complete binary tree from Wikipedia:
# In a complete binary tree every level, except possibly the last, is completely filled, 
# and all nodes in the last level are as far left as possible. 
# It can have between 1 and 2h nodes inclusive at the last level h.

class countNodes:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        buff = [root] if root else []
        total = 0
        while buff:
            
            tmp = []
            for n in buff:
                if n.left:
                    tmp.append(n.left)
                if n.right:
                    tmp.append(n.right)
                    
                total += 1
            
            buff = tmp
            
        return total

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def search(node):
            if not node:
                return 0

            left, right, height = node, node, 0

            while right:
                left = left.left
                right = right.right

                height += 1

            if not left:
                return int(max.pow(2, height) - 1)
            else:
                return search(root.left) + search(root.right) + 1

        return search(root)

    
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def search(node):
            if not node:
                return 0

            return search(node.left) + search(node.right) + 1

        return search(node)

if __name__=="__main__":

    pass