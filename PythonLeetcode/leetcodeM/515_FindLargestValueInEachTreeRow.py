"""
515. Find Largest Value in Each Tree Row


Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).

 

 

Example 1:


Input: root = [1,3,2,5,3,null,9]
Output: [1,3,9]
Example 2:

Input: root = [1,2,3]
Output: [1,3]
Example 3:

Input: root = [1]
Output: [1]
Example 4:

Input: root = [1,null,2]
Output: [1,2]
Example 5:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree will be in the range [0, 104].
-2^31 <= Node.val <= 2^31 - 1


"""


class LargestValueInEachTreeRow:

    def doit_search(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        from collections import deque
        if not root: return []

        buff = deque([root])
        res = []
        
        while buff:
            maxv = float('-inf')             
            for _ in range(len(buff)):
                n = buff.popleft()
                maxv = max(maxv, n.val)
                if n.left:
                    buff.append(n.left)
                if n.right:
                    buff.append(n.right)

            res.append(maxv)

        return res

    def largestValues(self, root: TreeNode) -> List[int]:

        def search_tree(node, rank):
            if not node:
                return
            
            val = node.val
            
            if rank in rank_vals:
                rank_vals[rank] = max(rank_vals[rank], val)
            else:
                rank_vals[rank] = val
            
            search_tree(node.right, rank+1)
            search_tree(node.left, rank+1)
        
        rank_vals = dict()
        search_tree(root, 0)
        
        return rank_vals.values()