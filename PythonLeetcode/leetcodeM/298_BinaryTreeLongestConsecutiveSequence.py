"""
298. Binary Tree Longest Consecutive Sequence

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. 
The longest consecutive path need to be from parent to child (cannot be the reverse).

Example 1:

Input:

   1
    \
     3
    / \
   2   4
        \
         5

Output: 3

Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
Example 2:

Input:

   2
    \
     3
    / 
   2    
  / 
 1

Output: 2 
Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class LongestConsecutiveBST:

    """
        Approach #1 (Top Down Depth-first Search) [Accepted]
        
        Algorithm

        A top down approach is similar to an in-order traversal. We use a variable length to store the current consecutive path length and pass it down the tree. 
        As we traverse, we compare the current node with its parent node to determine if it is consecutive. If not, we reset the length.

        Complexity analysis

        Time complexity : O(n). The time complexity is the same as an in-order traversal of a binary tree with nn nodes.

        Space complexity : O(n). The extra space comes from implicit stack space due to recursion. For a skewed binary tree, the recursion could go up to nn levels deep.
    """
    def doit_topdown(self, root: 'TreeNode') -> int:

        length = 0

        def search(node, val, l):
            nonlocal length
            if not node:
                length = max(length, l)
                return

            if node.val == val+1:
                length = max(length, l+1)
            else:
                l = 0

            search(node.left, node.val, l+1)
            search(node.right, node.val, l+1)

        search(root, float('inf'),0)
        return length
    
    def doit_topdown_1(self, root) -> int:
        
        def search(node, parent, length):
            
            if not node: return length
            
            length = (length + 1) if parent and parent.val + 1 == node.val else 1
            
            return max(length, search(node.left, node, length), search(node.right, node, length))
            
        return search(root, None, 0)

    """
        Approach #2 (Bottom Up Depth-first Search) [Accepted]
        Algorithm

        The bottom-up approach is similar to a post-order traversal. We return the consecutive path length starting at current node to its parent. Then its parent can examine if its node value can be included in this consecutive path.

        Complexity analysis

        Time complexity : O(n). The time complexity is the same as a post-order traversal in a binary tree, which is O(n)O(n).

        Space complexity : O(n). The extra space comes from implicit stack space due to recursion. For a skewed binary tree, the recursion could go up to nn levels deep.
    """
    def doit_bottomup(self, root) ->int:

        maxlength = 0
        def search(node):
            nonlocal maxlength
            
            if not node:
                return 0

            l, r = search(node.left) + 1, search(node.right) + 1

            if node.left and node.left.val != node.val + 1:
                l = 1
            
            if node.right and node.right.val != node.val + 1:
                r = 1

            maxlength = max(maxlength, l, r)
            return max(l, r)

        search(root)
        return maxlength