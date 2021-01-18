"""
1644. Lowest Common Ancestor of a Binary Tree II


Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)". 
A descendant of a node x is a node y that is on the path from node x to some leaf node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.
Example 3:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
Output: null
Explanation: Node 10 does not exist in the tree, so return null.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
 

Follow up: Can you find the LCA traversing the tree, without checking nodes existence?


"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class LowestCommonAncestorOfBinaryTreeII:

    def doit_(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':

        lca = None
        
        def search(node):
            nonlocal lca
            if not node:
                return 0
            
            ans = 0
            if node.val == p.val:
                ans = 1
            if node.val == q.val:
                ans = -1
                
            l, r = search(node.left), search(node.right)
            
            if l * r == -1 or ans * l == -1 or ans * r == -1:
                lca = node
                return 2
            
            if 1 in (ans, l, r):
                return 1
            
            if -1 in (ans, l, r):
                return -1
            
            return ans
        
        search(root)
        return lca

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        def dfs(node):
            if not node:
                return None
            
            left = dfs(node.left)
            right = dfs(node.right)
            
            if left and right:
                return node, 2
            
            if node in [p, q]:
                if left or right:
                    return node, 2
                else:
                    return node, 1
                
            return left or right
            
        lca = dfs(root)        
        return  lca[0] if lca and lca[1] == 2 else None


if __name__ == '__main__':

    pass