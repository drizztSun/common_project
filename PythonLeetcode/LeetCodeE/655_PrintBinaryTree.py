
# 655. Print Binary Tree

# Print a binary tree in an m*n 2D string array following these rules:

# The row number m should be equal to the height of the given binary tree.
# The column number n should always be an odd number.

# The root node's value (in string format) should be put in the exactly middle of the first row it can be put. 
# The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and right-bottom part). 
# You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. 
# The left-bottom part and the right-bottom part should have the same size. 
# Even if one subtree is none while the other is not, you don't need to print anything for the none subtree 
# but still need to leave the space as large as that for the other subtree. However, if two subtrees are none, then you don't need to leave space for both of them.
# Each unused space should contain an empty string "".
# Print the subtrees following the same rules.

# Example 1:
# Input:
#     1
#    /
#   2
# Output:
# [["", "1", ""],
#  ["2", "", ""]]

# Example 2:
# Input:
#     1
#    / \
#   2   3
#    \
#     4
# Output:
# [["", "", "", "1", "", "", ""],
#  ["", "2", "", "", "", "3", ""],
#  ["", "", "4", "", "", "", ""]]

# Example 3:
# Input:
#      1
#     / \
#    2   5
#   / 
#  3 
# / 
#4 
# Output:

# [["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
#  ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
#  ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
#  ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class PrintTree:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[str]]
        """
        st = [root]
        depth = 0

        while st:
            tmp = []
            for s in st:
                if s.left:
                    tmp.append(s.left)
                if s.right:
                    tmp.append(s.right)

            depth += 1
            st = tmp

        m, n = depth, 2**depth - 1
        res = [["" for _ in range(n)] for _ in range(m)]

        def fill(node, res, i, j, s):
            res[i][j] = str(node.val)
            
            if node.left:
                fill(node.left, res, i+1, j - s//2 - 1, s//2)
            if node.right:
                fill(node.right, res, i+1, j + s//2 + 1, s//2)

        fill(root, res, 0, n//2, n//2)
        return res


class Solution(object):
    def printTree(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[str]]
        """
        n = self.depthOfBinaryTree(root)
        m = (2 ** (n)) - 1
        
        matrix = [[""] * m for _ in range(n)]
        self.fillMatrix(matrix, root, 0, 0, m - 1)
        return matrix
        
    def depthOfBinaryTree(self, root):
        if not root:
            return 0
        
        return 1 + max(self.depthOfBinaryTree(root.left), self.depthOfBinaryTree(root.right))
    
    def fillMatrix(self, matrix, root, row, start, width):
        if not root:
            return
        
        mid = (start + width) / 2
        matrix[row][mid] = str(root.val)
        
        self.fillMatrix(matrix, root.left, row + 1, start, mid - 1)
        self.fillMatrix(matrix, root.right, row + 1, mid + 1, width)


if __name__ == "__main__":

    root = TreeNode(1)
    root.left = TreeNode(2)

    res = PrintTree().doit(root)

    root.right = TreeNode(5)
    root.left.left = TreeNode(3)
    root.left.left.left = TreeNode(4)

    res = PrintTree().doit(root)

    res = 0

        
            

        

            
        
        
        
                    

