# 513. Find Bottom Left Tree Value


# Given a binary tree, find the leftmost value in the last row of the tree.

# Example 1:
# Input:

#    2
#   / \
#  1   3

# Output:
# 1

# Example 2: 
# Input:

#        1
#       / \
#      2   3
#     /   / \
#    4   5   6
#       /
#      7

# Output:
# 7
# Note: You may assume the tree (i.e., the given root node) is not NULL.

# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BottomLeftTreeValue(object):

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.mostleft = (root.val, 0)
        def search(node, depth):
            
            if not node.left and not node.right and depth > self.mostleft[1]:
                self.mostleft = (node.val, depth)

            if node.left:
                search(node.left, depth + 1)
            if node.right:
                search(node.right, depth + 1)

        search(root, 0)
        return self.mostleft[0]
            
    # bfs
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        res = (root.val, 0)
        bfs = [(root, 0)]

        while bfs:

            N = len(bfs)
            for _ in range(N):
                c, d = bfs.pop(0)
                if not c.left and not c.right and d > res[1]:
                    res = (c.val, d)
                
                if c.left:
                    bfs.append((c.left, d + 1))

                if c.right:
                    bfs.append((c.right, d + 1))

        return res[0]


    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        bl = (0,0,root)
        bfs = [bl]
        
        while bfs:
            depth, left_num, node = bfs.pop()

            if node.left or node.right:

                if node.left:
                    bfs.append((depth+1, left_num+1, node.left))

                if node.right:
                    bfs.append((depth+1, left_num, node.right))
            else:
                #do the comparison, if any one of depth and letf_num is higher, replace
                bl_depth, bl_left, _  = bl

                if (depth > bl_depth) or  ((depth == bl_depth) and (left_num > bl_left)):
                    #replace
                    bl = (depth, left_num, node)

        return bl[2].val      

if __name__ == "__main__":

    root = TreeNode(1)
    root.right = TreeNode(3)
    root.left = TreeNode(2)
    root.left.left = TreeNode(4)
    root.right.left = TreeNode(5)
    root.right.right = TreeNode(6)
    root.right.left.left = TreeNode(7)

    res = BottomLeftTreeValue().doit(root)

    