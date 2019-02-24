# 783. Minimum Distance Between BST Nodes

# Given a Binary Search Tree (BST) with the root node root, return the minimum difference 
# between the values of any two different nodes in the tree.

# Example :

# Input: root = [4,2,6,1,3,null,null]
# Output: 1
# Explanation:
# Note that root is a TreeNode object, not an array.

# The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

#          4
#        /   \
#      2      6
#     / \    
#    1   3  

# while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.


class MinDiffInBST:

    def doit(self, root: TreeNode) -> int:
        
        def search(node):
            
            if not node.left and not node.right:
                return [node.val, node.val, float('inf')]
            
            res = [node.val, node.val, float('inf')]
            
            if node.left:
                c = search(node.left)
                res[0] = c[0]
                res[2] = min(c[2], node.val - c[1])
            if node.right:
                c = search(node.right)
                res[1] = c[1]
                res[2] = min(c[2], c[0] - node.val, res[2])
            
            return res
    
        return search(root)[2]

    def doit1(self, root: TreeNode) -> int:

        buff = [float('-inf'), float('inf')]

        def search(node):

            if not node:
                return

            search(node.left)

            buff[1] = min(node.val - buff[0], buff[1])
            buff[0] = node.val
            
            search(node.right)

        search(root)
        return buff[1]