# 572. Subtree of Another Tree

# Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s.
# A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

# Example 1:
# Given tree s:

#      3
#     / \
#    4   5
#   / \
#  1   2
# Given tree t:
#    4 
#   / \
#  1   2
# Return true, because t has the same structure and node values with a subtree of s.

# Example 2:
# Given tree s:

#      3
#     / \
#    4   5
#   / \
#  1   2
#     /
#    0
# Given tree t:
#    4
#   / \
#  1   2
# Return false.


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class SubtreeInAnotherTree:

    def doit(self, s, t):
        """
        :type s: TreeNode
        :type t: TreeNode
        :rtype: bool
        """
        def search(n1, n2):
            if n1 == n2 == None:
                return True
            
            if n1 and n2 and n1.val == n2.val:
                return search(n1.left, n2.left) and search(n1.right, n2.right)

            return False


        buff = [s]

        while buff:
            n = buff.pop(0)
            if n.val == t.val and search(n, t):
                return True

            if n.left:
                buff.append(n.left)
            
            if n.right:
                buff.append(n.right)

        return False


    def doit1(self, s, t):
        """
        :type s: TreeNode
        :type t: TreeNode
        :rtype: bool
        """
        from collections import deque as dq

        def traverse(source, target, ret):
            level = [(source, target)]
            target_head = target.val

            while level:
                new_level = []
                for elem_s, elem_t in level:
                    if elem_s.val != elem_t.val:
                        return False
                    else:
                        if elem_s.left and elem_t.left:
                            if elem_s.left.val == target_head:
                                ret.append(elem_s.left)
                            new_level.append((elem_s.left, elem_t.left))    
                        elif elem_s.left or elem_t.left:
                            return False

                        if elem_s.right and elem_t.right:
                            if elem_s.right.val == target_head:
                                ret.append(elem_s.right)
                            new_level.append((elem_s.right, elem_t.right))
                        elif elem_s.right or elem_t.right:
                            return False

                level = new_level

            return True

        if not s and not t:
            return True
        elif not s or not t:
            return False

        s_queue = dq([s])
        
        while s_queue:
            elem = s_queue.popleft()
            if elem.val == t.val:
                ret = []
                if traverse(elem, t, ret):
                    return True
                else:
                    for elem in ret:
                        s_queue.appendleft(elem)

            if elem.left:
                s_queue.append(elem.left)

            if elem.right:
                s_queue.append(elem.right)
        
        return False


if __name__ == "__main__":

    pass        
        