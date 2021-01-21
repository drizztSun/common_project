"""
701. Insert into a Binary Search Tree


You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

 

Example 1:


Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: Another accepted tree is:

Example 2:

Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]
Example 3:

Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
Output: [4,2,7,1,3,5]
 

Constraints:

The number of nodes in the tree will be in the range [0, 104].
-10^8 <= Node.val <= 10^8
All the values Node.val are unique.
-10^8 <= val <= 10^8
It's guaranteed that val does not exist in the original BST.


"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class InsertIntoBST:

    def doit_(self, root: 'TreeNode', val: int) -> 'TreeNode':
        """
        :type root: TreeNode
        :type val: int
        :rtype: TreeNode
        """
        if not root: return TreeNode(val)

        c = TreeNode(val)
        node = root
        
        while node:

            if node.val > val:
                if not node.left:
                    node.left = c
                    break
                else:
                    node = node.left

            else:
                if not node.right:
                    node.right = c
                    break
                else:
                    node = node.right

        return root

    def doit_(self, root: 'TreeNode', val: int) -> 'TreeNode':
        
        if not root: return TreeNode(val)
        
        current, previous = root, None
        
        while current:
            previous = current
            if current.val > val:
                current = current.left
            else:
                current = current.right
                
        if previous.val < val:
            previous.right = TreeNode(val)
        else:
            previous.left = TreeNode(val)
            
        return root