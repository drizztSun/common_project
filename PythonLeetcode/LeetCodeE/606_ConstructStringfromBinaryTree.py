# 606. Construct String from Binary Tree

# You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

# The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs 
# that don't affect the one-to-one mapping relationship between the string and the original binary tree.

# Example 1:
# Input: Binary tree: [1,2,3,4]
#       1
#     /   \
#    2     3
#   /    
#  4     

# Output: "1(2(4))(3)"

# Explanation: Originallay it needs to be "1(2(4)())(3()())", 
# but you need to omit all the unnecessary empty parenthesis pairs. 
# And it will be "1(2(4))(3)".
# Example 2:
# Input: Binary tree: [1,2,3,null,4]
#       1
#     /   \
#    2     3
#     \  
#      4 

# Output: "1(2()(4))(3)"

# Explanation: Almost the same as the first example, 
# except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.



class Tree2str:
    
    def doit(self, t):
        """
        :type t: TreeNode
        :rtype: str
        """
        def search(node):

            if not node:
                return ''

            tmp = str(node.val)

            if not node.left and not node.right:
                return tmp

            tmp += '(' + search(node.left) + ')' 
            if node.right:
                tmp += '(' + search(node.right) + ')'
            
            return tmp

        return search(t)


    def doit2(self, t):
        """
        :type t: TreeNode
        :rtype: str
        """
        def traver(root):
            if not root:
                return "()"
            elif not root.left and not root.right:
                return "{}".format(root.val)
            elif not root.right:
                return "{}({})".format(root.val, traver(root.left))
            elif not root.left:
                return "{}()({})".format(root.val, traver(root.right))
            else:
                return "{}({})({})".format(root.val, traver(root.left), traver(root.right))
        
        if not t:
            return ""

        return traver(t)    

    def doit1(self, t):
        """
        :type t: TreeNode
        :rtype: str
        """
        node = t
        buff = []
        res = ''
        count = 0

        while node or buff:

            if node:

                if count > 0:
                    res += '('
                
                count += 1                                     
                res += str(node.val)

                if node.right:
                    buff.append((node.right, count))

                node = node.left

            else:
                
                c = buff.pop()
                if c[1] == count:
                    res += '()'
                else:
                    res += ')' * (count - c[1])
                    count = c[1]

                node = c[0]

        return res + ')' * (count - 1)
    

                


            


            



