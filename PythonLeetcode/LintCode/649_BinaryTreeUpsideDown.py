"""
Definition of TreeNode:
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None
"""

class Solution:
    """
    @param root: the root of binary tree
    @return: new root
    """
    def upsideDownBinaryTree(self, root):
        # write your code here
        if not root:
            return None
            
        st, node = [], root
        while node:
            st.append(node)
            node = node.left
        
        root = st.pop()
        node = root
        while st:
            n = st.pop()
            node.right = n
            node.left = n.right
            
            node = node.right
            node.left, node.right = None, None
            
        return root