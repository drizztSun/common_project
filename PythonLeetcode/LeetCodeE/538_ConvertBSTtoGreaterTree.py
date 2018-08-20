# 538. Convert BST to Greater Tree

# Given a Binary Search Tree (BST), convert it to a Greater Tree such
# that every key of the original BST is changed to the original key plus 
# sum of all keys greater than the original key in BST.

# Example:

# Input: The root of a Binary Search Tree like this:
#              5
#            /   \
#           2     13

# Output: The root of a Greater Tree like this:
#             18
#            /   \
#          20     13



# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class ConvertBST:
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """

        def search(node, v):

            if not node.left and not node.right:
                node.val += v
                return node.val

            total = search(node.right, v) if node.right else v

            node.val += total
            
            total = search(node.left, node.val) if node.left else node.val
        
            return total
    

        if not root:
            return root

        search(root, 0)
        return root


    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        if not root:
            return root

        node, total = root, 0
        buff = []
        
        while node or buff:

            if node:

                buff.append(node)

                node = node.right

            else:

                n = buff.pop()
                n.val += total
                total = n.val

                node = n.left


        return root
        

if __name__ == "__main__":

    root = TreeNode(5)
    root.left = TreeNode(2)
    root.right = TreeNode(13)

    res = ConvertBST().doit(root)

            