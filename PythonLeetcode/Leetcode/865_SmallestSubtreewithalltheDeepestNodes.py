# 865. Smallest Subtree with all the Deepest Nodes

# Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.

# A node is deepest if it has the largest depth possible among any node in the entire tree.

# The subtree of a node is that node, plus the set of all descendants of that node.

# Return the node with the largest depth such that it contains all the deepest nodes in its subtree.

 

# Example 1:

# Input: [3,5,1,6,2,0,8,null,null,7,4]
# Output: [2,7,4]
# Explanation:



# We return the node with value 2, colored in yellow in the diagram.
# The nodes colored in blue are the deepest nodes of the tree.
# The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
# The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
# Both the input and output have TreeNode type.
 

# Note:

# The number of nodes in the tree will be between 1 and 500.
# The values of each node are unique.

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class SubtreeWithAllDeepest:

    def doit(self, root: 'TreeNode') -> 'TreeNode':

        self.res, self.deep = None, 0

        def search(node, deep):

            if not node:
                return deep

            left = search(node.left, deep + 1)
            right = search(node.right, deep + 1)

            lvl = max(left, right)

            if lvl > self.deep:
                self.deep = lvl
            
            if self.deep == left == right:
                self.res = node

            return lvl

        search(root, 0)

        return self.res


# Approach 1: Paint Deepest Nodes
# Intuition

# We try a straightforward approach that has two phases.

# The first phase is to identify the nodes of the tree that are deepest. To do this, we have to annotate the depth of each node. We can do this with a depth first search.

# Afterwards, we will use that annotation to help us find the answer:

# If the node in question has maximum depth, it is the answer.

# If both the left and right child of a node have a deepest descendant, then the answer is this parent node.

# Otherwise, if some child has a deepest descendant, then the answer is that child.

# Otherwise, the answer for this subtree doesn't exist.

# Algorithm

# In the first phase, we use a depth first search dfs to annotate our nodes.

# In the second phase, we also use a depth first search answer(node), returning the answer for the subtree at that node, 
# and using the rules above to build our answer from the answers of the children of node.

# Note that in this approach, the answer function returns answers that have the deepest nodes of the entire tree, 
# not just the subtree being considered.

    def doit1(self, root: 'TreeNode') -> 'TreeNode':

        depth = {None: -1}
        
        def dfs(node, parent):

            if node:
                depth[node] = depth[parent] + 1
                
                dfs(node.left, node)
                dfs(node.right, npde)
        
        dfs(root)

        maxdepth = max(depth.values())

        def answer(node):

            if not node or depth[node] == maxdepth:
                return node

            L, R = answer(node.left), answer(node.right)

            return node if L and R else L or R

        return answer(root)
        
           

        