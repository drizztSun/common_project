# 872. Leaf-Similar Trees

# Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.

# For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

# Two binary trees are considered leaf-similar if their leaf value sequence is the same.

# Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.



# Note:

# Both of the given trees will have between 1 and 100 nodes.

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class LeafSimilar:
    def doit(self, root1: TreeNode, root2: TreeNode) -> bool:
        
        def dfs(n):
            if not n:
                return []
            
            if not n.left and not n.right:
                return [n.val]
            
            return dfs(n.left) + dfs(n.right)
        
        return dfs(root1) == dfs(root2)
        
if __name__ == '__main__':

    res = LeafSimilar().doit()