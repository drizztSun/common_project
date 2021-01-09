"""
545. Boundary of Binary Tree

A binary tree boundary is the set of nodes (no duplicates) denoting the union of the left boundary, leaves, and right boundary.

The left boundary is the set of nodes on the path from the root to the left-most node. The right boundary is the set of nodes on the path from the root to the right-most node.

The left-most node is the leaf node you reach when you always travel to the left subtree if it exists and the right subtree if it doesn't. 
The right-most node is defined in the same way except with left and right exchanged. Note that the root may be the left-most and/or right-most node.

Given the root of a binary tree, return the values of its boundary in a counter-clockwise direction starting from the root.

 

Example 1:


Input: root = [1,null,2,3,4]
Output: [1,3,4,2]
Explanation:
The left boundary is the nodes [1,2,3].
The right boundary is the nodes [1,2,4].
The leaves are nodes [3,4].
Unioning the sets together gives [1,2,3,4], which is [1,3,4,2] in counter-clockwise order.
Example 2:


Input: root = [1,2,3,4,5,6,null,null,null,7,8,9,10]
Output: [1,2,4,7,8,9,10,6,3]
Explanation:
The left boundary are node 1,2,4. (4 is the left-most node according to definition)
The left boundary is nodes [1,2,4].
The right boundary is nodes [1,3,6,10].
The leaves are nodes [4,7,8,9,10].
Unioning the sets together gives [1,2,3,4,6,7,8,9,10], which is [1,2,4,7,8,9,10,6,3] in counter-clockwise order.
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000


"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class BoundaryOfBinaryTree:

    def doit_search(self, root: 'TreeNode') -> list:

        def search(node, edge, r):
            nonlocal path
            if not node: return
            
            if (not node.left and not node.right) or edge:
                path.append(node.val)
            
            if r:
                if node.right:
                    search(node.right, edge, r)
                if node.left:
                    search(node.left, edge and not node.right, r)
            else:
                if node.left:
                    search(node.left, edge, r)
                if node.right:
                    search(node.right, edge and not node.left, r)
        
        if not root: return [];
        
        path = []
        search(root.left, True, False)
        n = len(path)
        search(root.right, True, True)
        
        path[n:] = path[n:][::-1]
        return [root.val] + path


    
    def boundaryOfBinaryTree(self, root: TreeNode) -> List[int]:
        
        '''
        Idea: 2 different post order traversals
        have a boolean flag to know if im still on exterior or not
        and add if I am or if im at a leaf.
        '''

        def left(self, root, flag, arr):
        '''
        left most and leaf preorder traversal
        '''
        
            if not root:
                return 
            
            if not root.left and not root.right:
                arr.append(root.val)
                return
            
            if flag:
                arr.append(root.val)
                
            left(root.left, flag, arr)
            left(root.right, flag and not root.left, arr)
            
        def right(root, flag, arr):
            '''
            rightmost and leaf preorder traversal
            add to array only when we pop off to get reverse order
            '''
            
            if not root:
                return 
            
            if not root.left and not root.right:
                arr.append(root.val)
                return
            
            right(root.left, flag and not root.right, arr)
            right(root.right, flag, arr)
            
            if flag:
                arr.append(root.val)
            
        if not root:
            return
        
        
        ans = [root.val]
        left(root.left, True, ans)
        right(root.right, True, ans)
        
        return ans



if __name__ == '__main__':

    root = TreeNode(1)
    root.right = TreeNode(2)
    root.right.left = TreeNode(3)
    root.right.right = TreeNode(4)

    BoundaryOfBinaryTree().doit_search(root)


        