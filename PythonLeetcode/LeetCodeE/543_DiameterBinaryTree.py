# 543. Diameter of Binary Tree

# Given a binary tree, you need to compute the length of the diameter of the tree. 
# The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
# This path may or may not pass through the root.

# Example:
# Given a binary tree 
#          1
#         / \
#        2   3
#       / \     
#      4   5    
# Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

# Note: The length of path between two nodes is represented by the number of edges between them.

# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class DiameterOfBinaryTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def search(node):

            if not node:
                return 0, 0

            maxcl, maxl = search(node.left)

            maxcr, maxr = search(node.right)

            return (max(maxcr, maccl, maxl + maxr + 1), max(maxl, maxr) + 1)

        return max(search(root))


    def doit1(self, root):

        """
        :type root: TreeNode
        :rtype: int
        """        
        def heightDiameter(root):
            if not root:
                return (0, 0)
            else:
                left_height, left_diameter = self.heightDiameter(root.left)
                right_height, right_diameter = self.heightDiameter(root.right)
            
                temp_diameter = left_height + right_height 
                height = max(left_height, right_height) + 1

                if left_diameter > temp_diameter and left_diameter > right_diameter:
                    return (height, left_diameter)

                elif right_diameter > temp_diameter and right_diameter > left_diameter:
                    return (height, right_diameter)

                else:
                    return (height, temp_diameter)

        return heightDiameter(root)[1] if root else 0


if __name__ == "__main__":

    res = DiameterOfBinaryTree().doit(None)