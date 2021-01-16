"""
113. Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class PathSumII:

    def doit_dfs(self, root: 'TreeNode', sum: int) -> list:
        
        if not root: return []
        
        ans = []
        def build(node, path, total):
            nonlocal ans
            if not node.left and not node.right:
                if total + node.val == sum:
                    ans.append(path + [node.val])
                return
            
            total += node.val
            path.append(node.val)
            
            if node.left:
                build(node.left, path, total)
                
            if node.right:
                build(node.right, path, total)
                
            path.pop()
            
        build(root, [], 0)
        
        return ans

    """
        Approach: Depth First Traversal | Recursion
        Intuition

        The intuition for this approach is pretty straightforward. The problem statement asks us to find all root to leaf paths in a given binary tree. 
        If you simply consider the depth first traversal on a tree, all it does is traverse once branch after another. All we need to do here is to simply execute the depth first traversal and maintain two things along the way:

        A running sum of all the nodes traversed till that point in recursion and
        A list of all those nodes
        If ever the sum becomes equal to the required sum, and the node where this happens is a leaf node, we can simply add the list of nodes to our final solution. 
        We keep on doing this for every branch of the tree and we will get all the root to leaf paths in this manner that add up to a certain value. Basically, these paths are branches and hence the depth first traversal makes the most sense here. We can also use the breadth first approach for solving this problem. However, that would be super heavy on memory and is not a recommended approach for this very problem. We will look into more details towards the end.

        Algorithm

        1. We'll define a function called recurseTree which will take the following parameters

        node which represents the current node we are on during recursion
        remainingSum which represents the remaining sum that we need to find going down the tree. We can also pass the current sum in our recursive calls. However, then we'd also need to pass the required sum as an additional variable since we'd have to compare the current sum against that value. By passing in remaining sum, we can avoid having to pass additional variable and just see if the remaining sum is 0 (or equal to the value of the current node).
        Finally, we'll have to pass a list of nodes here which will simply contain the list of all the nodes we have seen till now on the current branch. Let's call this pathNodes.
        The following examples assume the sum to be found is 22.
        
                
        2. At every step along the way, we will simply check if the remaining sum is equal to the value of the current node. If that is the case and the current node is a leaf node, we will add the current pathNodes to the final list of paths that we have to return as a result.


        3. The problem statement here specifically mentions root to leaf paths. A slight modification is to find all root to node paths. The solutions are almost similar except that we'd get rid of the leaf check.

        An important thing to consider for this modification is that the problem statement doesn't mention anything about the values of the nodes. That means, we can't assume them to be positive. Had the values been positive, we could stop at the node where the sum became equal to the node's value.
        However, if the values of the nodes can be negative, then we have to traverse all the branches, all the way up to the roots. Let's look at a modified tree for reference.

    """
    def pathSum(self, root: 'TreeNode', sum: int) -> list:
        pathsList = []
        
        def recurseTree(node, remainingSum, pathNodes, pathsList):
        
            if not node:
                return 
            
            # Add the current node to the path's list
            pathNodes.append(node.val)
            
            # Check if the current node is a leaf and also, if it
            # equals our remaining sum. If it does, we add the path to
            # our list of paths
            if remainingSum == node.val and not node.left and not node.right:
                pathsList.append(list(pathNodes))
            else:    
                # Else, we will recurse on the left and the right children
                recurseTree(node.left, remainingSum - node.val, pathNodes, pathsList)
                recurseTree(node.right, remainingSum - node.val, pathNodes, pathsList)
                
            # We need to pop the node once we are done processing ALL of it's
            # subtrees.
            pathNodes.pop()

        recurseTree(root, sum, [], pathsList)
        return pathsList