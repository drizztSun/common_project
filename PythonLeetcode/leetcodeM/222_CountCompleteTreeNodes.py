"""
222. Count Complete Tree Nodes

Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: 6
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [1]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [0, 5 * 104].
0 <= Node.val <= 5 * 104
The tree is guaranteed to be complete.
 

Follow up: Traversing the tree to count the number of nodes in the tree is an easy solution but with O(n) complexity. Could you find a faster algorithm?


"""


class CountNodes:

    """ 
        Approach 2: Binary search
        Intuition

        Approach 1 doesn't profit from the fact that the tree is a complete one.

        In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible.

        That means that complete tree has 2^k nodes in the kth level if the kth level is not the last one. The last level may be not filled completely, and hence in the last level the number of nodes could vary from 1 to 2^d, where d is a tree depth.

    """
    
    def doir_search(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def search(node):
            if not node:
                return 0

            return search(node.left) + search(node.right) + 1

        return search(root)


    def doit_bfs(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        buff = [root] if root else []
        total = 0
        while buff:
            
            tmp = []
            for n in buff:
                if n.left:
                    tmp.append(n.left)
                if n.right:
                    tmp.append(n.right)
                    
                total += 1
            
            buff = tmp
            
        return total


class CountNode_logn:
    
    def compute_depth(self, node: 'TreeNode') -> int:
        """
        Return tree depth in O(d) time.
        """
        d = 0
        while node.left:
            node = node.left
            d += 1
        return d

    def exists(self, idx: int, d: int, node: 'TreeNode') -> bool:
        """
        Last level nodes are enumerated from 0 to 2**d - 1 (left -> right).
        Return True if last level node idx exists. 
        Binary search with O(d) complexity.
        """
        left, right = 0, 2**d - 1
        for _ in range(d):
            pivot = left + (right - left) // 2
            if idx <= pivot:
                node = node.left
                right = pivot
            else:
                node = node.right
                left = pivot + 1
        return node is not None
        
    def countNodes(self, root: 'TreeNode') -> int:
        # if the tree is empty
        if not root:
            return 0
        
        d = self.compute_depth(root)
        # if the tree contains 1 node
        if d == 0:
            return 1
        
        # Last level nodes are enumerated from 0 to 2**d - 1 (left -> right).
        # Perform binary search to check how many nodes exist.
        left, right = 1, 2**d - 1
        while left <= right:
            pivot = left + (right - left) // 2
            if self.exists(pivot, d, root):
                left = pivot + 1
            else:
                right = pivot - 1
        
        # The tree contains 2**d - 1 nodes on the first (d - 1) levels
        # and left nodes on the last level.
        return (2**d - 1) + left