"""
1110. Delete Nodes And Return Forest

Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the result in any order.

 

Example 1:



Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
 

Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class DeleteNodeAndReturnForest:

    def doit_search(self, root: 'TreeNode', to_delete: 'List[int]') -> 'List[TreeNode]':
        
        ans = []
        to_delete = set(to_delete)
        def build(node, parent, beleft):
            nonlocal ans, to_delete
            if not node: return
            
            if node.val in to_delete:
                if parent:
                    if beleft:
                        parent.left = None
                    else:
                        parent.right = None
                parent = None
            else:
                if parent == None:
                    ans.append(node)
                parent = node
                
            build(node.left, parent, True)
            build(node.right, parent, False)
            
        build(root, None, True)
        return ans
        