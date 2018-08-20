# 501. Find Mode in Binary Search Tree


# Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

# Assume a BST is defined as follows:

# The left subtree of a node contains only nodes with keys less than or equal to the node's key.
# The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
# Both the left and right subtrees must also be binary search trees.
 

# For example:
# Given BST [1,null,2,2],

#   1
#    \
#     2
#    /
#   2
 

# return [2].

# Note: If a tree has more than one mode, you can return them in any order.

# Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None




class FindModeInBST:

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        buff = [root]
        cnt = {}
        maxv = [0, set()]

        while buff:

            length = len(buff)
            for _ in range(length):

                node = buff.pop(0)

                cnt[node.val] = cnt.get(node.val, 0) + 1
                if cnt[node.val] == maxv[0]:
                    maxv[1].add(node.val)
                elif cnt[node.val] > maxv[0]:
                    maxv = [0, set()]
                    maxv[0] = cnt[node.val] 
                    maxv[1].add(node.val)

                if node.left:
                    buff.append(node.left)

                if node.right:
                    buff.append(node.right)

        return list(maxv[1])    


    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if not root:
            return []
        
        buff = [root]
        cnt = {}
        maxv = [0, []]

        while buff:

            length = len(buff)
            for _ in range(length):

                node = buff.pop(0)
                
                cnt[node.val] = cnt.get(node.val, 0) + 1
                
                if cnt[node.val] == maxv[0]:
                    maxv[1].append(node.val)
                
                elif cnt[node.val] > maxv[0]:
                    maxv = [0, []]
                    maxv[0] = cnt[node.val] 
                    maxv[1].append(node.val)

                if node.left:
                    buff.append(node.left)

                if node.right:
                    buff.append(node.right)

        return maxv[1]


if __name__ == "__main__":

    root = TreeNode(1)

    root.right = TreeNode(2)
    root.right.left = TreeNode(2)

    res = FindModeInBST().doit(root)

    pass