# 515. Find Largest Value in Each Tree Row

# You need to find the largest value in each row of a binary tree.

# Example:
# Input: 

#          1
#         / \
#        3   2
#       / \   \  
#      5   3   9 

# Output: [1, 3, 9]


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class LargestValues:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if not root:
            return []

        buff = [root]

        while buff:
        
            newbuff = []
            maxv = 0            
            while buff:
                n = buff.pop()
                maxv = max(maxv, n.val)
                if n.left:
                    newbuff.append(n.left)
                if n.right:
                    newbuff.append(n.right)

            res.append(maxv)
            buff = newbuff

        return res


    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if root == None:
            return []

        max_values = []
        next_row = [root]

        while True:

            if len(next_row) == 0:
                return max_values

            current_row = next_row
            next_row = []
            current_row_max = current_row[0].val

            for node in current_row:
                if node.val > current_row_max:
                    current_row_max = node.val
                if node.left != None:
                    next_row.append(node.left)
                if node.right != None:
                    next_row.append(node.right)

            max_values.append(current_row_max)


if __name__ == "__main__":

    pass
    