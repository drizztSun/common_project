# 637. Average of Levels in Binary Tree

# Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
# Example 1:
# Input:
#    3
#   / \
#  9  20
#    /  \
#   15   7
# Output: [3, 14.5, 11]
# Explanation:
# The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
# Note:
# The range of node's value is in the range of 32-bit signed integer.



# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class AverageOfLevels:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[float]
        """
        buff = [root]
        res = []
        while buff:
            total = 0
            N = len(buff)
            newBuff = []
            for c in buff:
                total += c.val
                if c.left:
                    newBuff.append(c.left)
                if c.right:
                    newBuff.append(c.right)

            res.append(total / N)
            buff = newBuff

        return res


    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[float]
        """
        if not root:
            return []
        my_list = []
        stack = []
        stack.append(root)
        while stack:
            temp_list = []
            temp_stack = []

            for i in stack:

                temp_list.append(i.val)

                if i.left:
                    temp_stack.append(i.left)
                if i.right:
                    temp_stack.append(i.right)

            if temp_list:
                my_list.append(sum(temp_list)/len(temp_list))

            stack = temp_stack

        return my_list



if __name__ == "__main__":

    root = TreeNode(3)

    root.left = TreeNode(9)
    root.right = TreeNode(20)

    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    res = AverageOfLevels().doit(root)
