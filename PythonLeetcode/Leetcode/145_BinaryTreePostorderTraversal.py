import os



class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None



# Leetcode 94. Binary Tree Inorder Traversal
# Definition for a binary tree node.
class inorderTraversal(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack, cur, result = [], root, []
        while cur or stack:
            while cur:
                stack.append(cur)
                cur = cur.left
            
            cur = stack.pop()
            result.append(cur.val)    
        
            cur = cur.right

        return result

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        def search(node):
            if not node:
                return []

            return search(node.left) + search(node.right) + [node.val]
            
        return search(root)


    def doit2(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur, buff, res = root, [], []

        while cur:

            if cur.left:
                buff.append(cur)
                cur = cur.left
            else:
                res.append(cur.val)
                while not cur.right and buff:
                    cur = buff.pop()
                    res.append(cur.val)

                cur = cur.right
               
        return res

        



# Leetcode 144. Binary Tree Preorder Traversal            
class preorderTraversal(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack, current, result = [], root, []
        while current or stack:

            if not current:
                current = stack.pop()

            result.append(current.val)

            if current.right:
                stack.append(current.right)

            current = current.left

        return result


    def doit2(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack, res = [root], []

        while stack:
            n = stack.pop()
            # LIFO, so left will gt out first
            if n :
                res.append(n.val)

                stack.append(n.right)
                stack.append(n.left)

        return res            
                

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        def search(node):
            if not node:
                return []
            return [node.val] + search(node.left) + search(node.right)

        return search(node)


    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur, stack, res = root, [], []

        while cur or stack:

            while cur:
                res.append(cur.val)
                stack.append(cur)
                cur = cur.left

            cur = stack.pop().right
            
        return res


# 145. Binary Tree Postorder Traversal
# Given a binary tree, return the postorder traversal of its nodes' values.

# For example:
# Given binary tree {1,#,2,3},

# 1
#  \
#   2
#  /
# 3
# return [3,2,1]

class postorderTraversal:
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        def search(node):
            if not node:
                return []

            return search(node.left) + search(node.right) + [node.val]

        return search(root)

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur, buff, res = root, [], []
        
        while cur or buff:

            while cur :
                res = [cur.val] + res
                buff.append(cur)
                cur = cur.right

            cur = buff.pop().left

        return res

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur, buff, res = root, [], []
        
        while cur or buff:

            while cur :
                res = [cur.val] + res
                buff.append(cur.left)
                cur = cur.right

            cur = buff.pop()

        return res

    def doit2(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        # sanity check
        if not root:
            return []
        
        # utils
        def LBL(p):
            # get left-bottom leaf under p
            #   p is in stack already
            nonlocal stack
            while p.left or p.right:
                if p.left:
                    if p.right:
                        stack.append(p.right)
                    stack.append(p.left)
                    p = p.left
                else:
                    stack.append(p.right)
                    p = p.right
        
        # use stack
        stack = []
        stack.append(root)
        LBL(stack[-1])
        
        ret = []
        
        while stack:
            p = stack.pop()
            ret.append(p.val)
            
            if stack and p != stack[-1].left and p != stack[-1].right:
                # r cousin at top
                LBL(stack[-1])
        
        return ret

if __name__=="__main__":


    pass