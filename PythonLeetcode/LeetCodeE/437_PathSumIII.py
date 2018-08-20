


# 437. Path Sum III

# You are given a binary tree in which each node contains an integer value.
# Find the number of paths that sum to a given value.
# The path does not need to start or end at the root or a leaf, but it must go downwards 
# (traveling only from parent nodes to child nodes).
# The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

# Example:

# root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

#      10
#     /  \
#    5   -3
#   / \    \
#  3   2   11
# / \   \
#3  -2   1

# Return 3. The paths that sum to 8 are:

# 1.  5 -> 3
# 2.  5 -> 2 -> 1
# 3. -3 -> 11


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class pathSum:

    def doit(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: int
        """
        def helper(self, root, target, so_far, cache):
            if root:
                complement = so_far + root.val - target
                if complement in cache:
                    result += cache[complement]
                
                cache.setdefault(so_far+root.val, 0)
                cache[so_far+root.val] += 1
                
                helper(root.left, target, so_far+root.val, cache)
                helper(root.right, target, so_far+root.val, cache)
                
                cache[so_far+root.val] -= 1
            return

        result = 0
        helper(root, sum, 0, {0:1})
        return result

    def doit(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: int
        """
        def search(node, value, start):

            res = 0
            if node.val == value:
                res += 1

            if node.left:
                res += search(node.left, value - node.val, start)
                if node.left not in start:
                    start.add(node.left)
                    res += search(node.left, sum, start)

            if node.right:
                res += search(node.right, value - node.val, start)
                if node.right not in start:
                    start.add(node.right)
                    res += search(node.right, sum, start)

            return res

        if not root:
            return 0
        
        return search(root, sum, set())
                                 


if __name__=="__main__":


    A = TreeNode(1)
    A.right = TreeNode(2)
    A.right.right = TreeNode(3)
    A.right.right.right = TreeNode(4)
    A.right.right.right.right = TreeNode(5)


    res = pathSum().doit(A, 3)


    pass