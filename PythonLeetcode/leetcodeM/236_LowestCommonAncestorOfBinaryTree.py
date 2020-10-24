"""
236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node
in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”



Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1


Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the tree.

"""


class LowestCommonAncestor:


    """
    Approach 1: Recursive Approach
    Intuition

    The approach is pretty intuitive. Traverse the tree in a depth first manner. The moment you encounter either of the nodes p or q, return some boolean flag. The flag helps to determine if we found the required nodes in any of the paths. The least common ancestor would then be the node for which both the subtree recursions return a True flag. It can also be the node which itself is one of p or q and for which one of the subtree recursions returns a True flag.

    Let us look at the formal algorithm based on this idea.

    Algorithm

    Start traversing the tree from the root node.
    If the current node itself is one of p or q, we would mark a variable mid as True and continue the search for the other node in the left and right branches.
    If either of the left or the right branch returns True, this means one of the two nodes was found below.
    If at any point in the traversal, any two of the three flags left, right or mid become True, this means we have found the lowest common ancestor for the nodes p and q.
    Let us look at a sample tree and we search for the lowest common ancestor of two nodes 9 and 11 in the tree.

    Complexity Analysis

    Time Complexity: O(N)O(N), where NN is the number of nodes in the binary tree. In the worst case we might be visiting all the nodes of the binary tree.

    Space Complexity: O(N)O(N). This is because the maximum amount of space utilized by the recursion stack would be NN since the height of a skewed binary tree could be NN.

    """
    def doit(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':

        self.ans = None

        def dfs(n):

            if not n:
                return 0

            left, right = dfs(n.left), dfs(n.right)

            mid = n == p or n == q

            if mid + right + left >= 2:
                self.ans = n

            return mid or left or right

        dfs(root)
        return self.ans

    """
    Approach 2: Iterative using parent pointers
    Intuition
    
    If we have parent pointers for each node we can traverse back from p and q to get their ancestors. The first common node we get during this traversal would be the LCA node. 
    We can save the parent pointers in a dictionary as we traverse the tree.
    
    Algorithm
    
    Start from the root node and traverse the tree.
    Until we find p and q both, keep storing the parent pointers in a dictionary.
    Once we have found both p and q, we get all the ancestors for p using the parent dictionary and add to a set called ancestors.
    Similarly, we traverse through ancestors for node q. If the ancestor is present in the ancestors set for p, 
    this means this is the first ancestor common between p and q (while traversing upwards) and hence this is the LCA node.

    """
    def doit(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """

        # Stack for tree traversal
        stack = [root]

        # Dictionary for parent pointers
        parent = {root: None}

        # Iterate until we find both the nodes p and q
        while p not in parent or q not in parent:

            node = stack.pop()

            # While traversing the tree, keep saving the parent pointers.
            if node.left:
                parent[node.left] = node
                stack.append(node.left)
            if node.right:
                parent[node.right] = node
                stack.append(node.right)

        # Ancestors set() for node p.
        ancestors = set()

        # Process all ancestors for node p using parent pointers.
        while p:
            ancestors.add(p)
            p = parent[p]

        # The first ancestor of q which appears in
        # p's ancestor set() is their lowest common ancestor.
        while q not in ancestors:
            q = parent[q]
        return q