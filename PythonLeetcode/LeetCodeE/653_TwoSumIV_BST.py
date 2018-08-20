# 653. Two Sum IV - Input is a BST


# Given a Binary Search Tree and a target number, return true if there exist two elements in the BST 
# such that their sum is equal to the given target.

# Example 1:
# Input: 
#     5
#    / \
#   3   6
#  / \   \
# 2   4   7

# Target = 9

# Output: True

# Example 2:
# Input: 
#     5
#    / \
#   3   6
#  / \   \
# 2   4   7

# Target = 28

# Output: False

# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class TwoSumIVInBST(object):


    def doit1(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: bool
        """
        if not root:
            return False
        
        buff, s = [root], set()
        
        while buff:
            n = buff.pop(0)
            
            if k - n.val in s:
                return True
            
            s.add(n.val)
            
            if n.left:
                buff.append(n.left)
                
            if n.right:
                buff.append(n.right)
                
        return False

    def doit(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: bool
        """
        mapping = {}
        buff = [root]

        while buff:
            n = buff.pop(0)
            
            mapping[n.val] = mapping.get(n.val, 0) + 1

            if n.left:
                buff.append(n.left)

            if n.right:
                buff.append(n.right)

        buff = [root]

        while buff:

            n = buff.pop(0):

            if k - n.val in mapping:
                if k - n.val != n.val or mapping[n.val] > 1:
                    return True
                
            if n.left:
                buff.append(n.left)

            if n.right:
                buff.append(n.right)

        return False


if __name__ == "__main__":

    pass