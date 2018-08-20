



# 404. Sum of Left Leaves

# Find the sum of all left leaves in a given binary tree.

# Example:

#    3
#   / \
#  9  20
#    /  \
#   15   7

# There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None



class sumOfLeftLeaves:

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def search(node):
            res = 0
            if not node:
                return res
            
            if node.left and not node.left.left and not node.left.right:
                res += node.left.val

            res += search(node.left) + search(node.right)

            return res
        
        return search(root)

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        node = root
        stack = []
        res = 0

        while node:

            if node.right:
                stack.append(node.right)

            if node.left and not node.left.left and not node.left.right:
                res += node.left.val
                node = None
            else:
                node = node.left

            if not node and stack:
                node = stack.pop()

        return res

        

if __name__=="__main__":

    a = TreeNode(3)
    a.left = TreeNode(9)
    a.right = TreeNode(20)
    a.right.left, a.right.right = TreeNode(15), TreeNode(7)

    res = sumOfLeftLeaves().doit(a)


    pass
        
