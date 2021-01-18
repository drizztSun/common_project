"""
1305. All Elements in Two Binary Search Trees


Given two binary search trees root1 and root2.

Return a list containing all the integers from both trees sorted in ascending order.

 

Example 1:


Input: root1 = [2,1,4], root2 = [1,0,3]
Output: [0,1,1,2,3,4]
Example 2:

Input: root1 = [0,-10,10], root2 = [5,1,7,0,2]
Output: [-10,0,0,1,2,5,7,10]
Example 3:

Input: root1 = [], root2 = [5,1,7,0,2]
Output: [0,1,2,5,7]
Example 4:

Input: root1 = [0,-10,10], root2 = []
Output: [-10,0,10]
Example 5:


Input: root1 = [1,null,8], root2 = [8,1]
Output: [1,1,8,8]
 

Constraints:

Each tree has at most 5000 nodes.
Each node's value is between [-10^5, 10^5].

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class AllElementsInTwoBinarySearchTree:

    def doit_dfs(self, root1: 'TreeNode', root2: 'TreeNode') -> list:

        def inorder(node):
            if not node: 
                return []
            return inorder(node.left) + [node.val] + inorder(node.right)
        
        root1_inorder, root2_inorder = inorder(root1), inorder(root2)
        i, j = 0, 0
        ans = []
        while i < len(root1_inorder) or j < len(root2_inorder):
            
            if i == len(root1_inorder):
                ans.append(root2_inorder[j])
                j += 1
            elif j == len(root2_inorder):
                ans.append(root1_inorder[i])
                i += 1
            else:
                if root2_inorder[j] > root1_inorder[i]:
                    ans.append(root1_inorder[i])
                    i += 1
                else:
                    ans.append(root2_inorder[j])
                    j += 1
                    
        return ans

    def doit_search(self, root1: 'TreeNode', root2: 'TreeNode') -> list:
        
        if not root1 and not root2:
            return [0]
        
        from collections import deque
        
        level = []
        integers = []
        
        if root1:
            level.append(root1)
            integers.append(root1.val)

        if root2:
            level.append(root2)
            integers.append(root2.val)

        while level:
            next_level = []
            for node in level:
                if node.left:
                    integers.append(node.left.val)
                    next_level.append(node.left)
                if node.right:
                    integers.append(node.right.val)
                    next_level.append(node.right)
            level = next_level
            
        return sorted(integers)

    def doit_search(self, root1: 'TreeNode', root2: 'TreeNode') -> list:
        l = []
        
        def recursive(node):
            if node is None:
                return
            recursive(node.left)
            l.append(node.val)
            recursive(node.right)
            
        recursive(root1)
        recursive(root2)
        return sorted(l)