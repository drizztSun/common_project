

# 96. Unique Binary Search Trees

# Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

# Example:

# Input: 3
# Output: 5
# Explanation:
# Given n = 3, there are a total of 5 unique BST's:

#   1         3     3      2      1
#    \       /     /      / \      \
#     3     2     1      1   3      2
#    /     /       \                 \
#   2     1         2                 3


class UniqueBinarySearchTree:

    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        def find(s, e, buff):
            if s >= e:
                return 1
            
            if (e - s) in buff:
                return buff[e - s]
            
            res = 0
            for i in range(s, e+1):
                l = find(s, i-1, buff)
                r = find(i + 1, e, buff)
                    
                res += l * r
            
            
            buff[e - s] = res
            return res
        
        
        return find(1, n, {})


# 95. Unique Binary Search Trees II

# Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

# Example:

# Input: 3
# Output:
# [
#  [1,null,3,2],
#  [3,2,null,1],
#  [3,1,null,null,2],
#  [2,1,3],
#  [1,null,2,null,3]
# ]
# Explanation:
# The above output corresponds to the 5 unique BST's shown below:

#   1         3     3      2      1
#    \       /     /      / \      \
#     3     2     1      1   3      2
#    /     /       \                 \
#   2     1         2                 3


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class UniqueBinarySearchTreeII:


    def doit(self, n):
        """
        :type n: 
        :rtype: List[TreeNode]
        """
        def helper(start, end):
            if (start, end) in memo:
                return memo[start, end]
            
            tree = []
            for root in range(start, end + 1):

                left_list = helper(start, root - 1)
                right_list = helper(root + 1, end)

                for left in left_list:
                    for right in right_list:
                        node = TreeNode(root)
                        node.left = left
                        node.right = right
                        tree.append(node)
                        
            memo[start, end] = tree or [None]
            return tree or [None]
        
        memo = {}
        if n == 0:
            return []
        return helper(1, n)


    def doit1(self, n):
        """
        :type n: 
        :rtype: List[TreeNode]
        """
        # we dont need to clone this one
        def clone(node):
            return node
            if not node:
                return None
    
            n = TreeNode(node.val)
            n.left, n.right = clone(node.left), clone(node.right)
            return n
        
        def build(scope, buff):
            if not scope:
                return []

            if len(scope) == 1:
                return [TreeNode(scope[0])]

            if buff[scope[0]][scope[-1]]:
                return buff[scope[0]][scope[-1]]

            res = []
            for i in range(len(scope)):
                
                left, right = build(scope[:i], buff), build(scope[i+1:], buff)
                if not left:
                    left.append(None)
                if not right:
                    right.append(None)

                
                for l in left:
                    for r in right:
                        n = TreeNode(scope[i])                    
                        n.left, n.right = clone(l), clone(r)

                        res.append(n)

            buff[scope[0]][scope[-1]] =res
            return res

        buff = [ [ [] for _ in range(n+1)] for _ in range(n+1) ]
        
        return build([x for x in range(1, n+1)], buff)

    def doit2(self, n):
        """
        :type n: 
        :rtype: List[TreeNode]
        """
        def clone(node):
            if not node:
                return None
    
            n = TreeNode(node.val)
            n.left, n.right = clone(node.left), clone(node.right)
            return n
        
        def build(scope):
            if not scope:
                return []

            if len(scope) == 1:
                return [TreeNode(scope[0])]

            res = []
            for i in range(len(scope)):
                
                left, right = build(scope[:i]), build(scope[i+1:])
                if not left:
                    left.append(None)
                if not right:
                    right.append(None)

                
                for l in left:
                    for r in right:
                        n = TreeNode(scope[i])                    
                        n.left, n.right = clone(l), clone(r)

                        res.append(n)
            return res

        return build([x for x in range(1, n+1)])



if __name__ == "__main__":

    pass
