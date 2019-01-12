# 652. Find Duplicate Subtrees

# Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

# Two trees are duplicate if they have the same structure with same node values.

# Example 1:

#         1
#        / \
#       2   3
#      /   / \
#     4   2   4
#        /
#       4
# The following are two duplicate subtrees:

#       2
#      /
#     4
# and

#     4
# Therefore, you need to return above trees' root in the form of a list.

import collections

class TreeNode:

    def __init__(self, v):
        self.val = v
        self.left = None
        self.right = None

class FindDuplicateSubtrees:
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[TreeNode]
        """
        
        buff = collections.defaultdict(list)
        
        def duplicate(node):
            #global buff
            
            if not node:
                return 'x '
            
            key = str(node.val) + ' ' + duplicate(node.left) + duplicate(node.right)
            
            if key not in buff:
                buff[key] = [node, 1]
            else:
                buff[key][1] += 1
                
            return key
        
        duplicate(root)
        
        return [ v[0] for v in buff.values() if v[1] > 1]


if __name__ == "__main__":

    root = TreeNode(1)

    root.left = TreeNode(2)
    root.right = TreeNode(3)

    root.left.left = TreeNode(4)
    root.right.left = TreeNode(2)
    root.right.right = TreeNode(4)

    root.right.left.left = TreeNode(4)

    res = FindDuplicateSubtrees().doit(root)