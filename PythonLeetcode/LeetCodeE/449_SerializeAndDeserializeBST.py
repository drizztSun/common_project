


# 449. Serialize and Deserialize BST


# Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

# Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

# The encoded string should be as compact as possible.

# Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None



# <BFS>
class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        :type root: TreeNode
        :rtype: str
        """
        stack = [root]
        res = ''
        while stack:
            tmp = []            
            while stack:
                node = stack.pop(0)

                if not res:
                    res = str(node.val) if node else 'N'
                else:
                    res += ',' + (str(node.val) if node else 'N')

                if node:
                    tmp.append(node.left)
                    tmp.append(node.right)

            stack = tmp

        return res

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        def next(data, i):
            if i >= len(data):
                return None
            s = i
            while i < len(data) and data[i] != ',':
                i += 1

            return data[s: i], i + 1 if i + 1 < len(data) else len(data)

        f, i = next(data, 0)
        root = None if f == 'N' else TreeNode(int(f))
        stack = [root]
        while  stack:

            tmp = []
            while stack and i < len(data):
                node = stack.pop(0)

                #left
                f, i = next(data, i)
                node.left = None if f == 'N' else TreeNode(int(f))
                if node.left:
                    tmp.append(node.left)

                # right
                f, i = next(data, i)
                node.right = None if f == 'N' else TreeNode(int(f))

                if node.right:
                    tmp.append(node.right)

            stack = tmp

        return root
                

# <DFS>
class Codec1:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def serial(node, result):
            if not node:
                result.append('N')
            else:
                result.append(str(node.val))
                serial(node.left, result)
                serial(node.right, result)
        
        result = []
        serial(root, result)
        return ','.join(result)


    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        dataSet = data.split(',')
        def deserial(A, i):
            if i >= len(A) or A[i] == 'N':
                return None, i + 1
            
            node = TreeNode(int(A[i]))

            node.left, i = deserial(A, i + 1)
            node.right, i = deserial(A, i)

            return node, i


        return deserial(dataSet, 0)[0]
        
if __name__=="__main__":

    a = TreeNode(1)
    a.left = TreeNode(2)
    a.right = TreeNode(3)

    a.left.left = TreeNode(4)

    a.right.left = TreeNode(5)
    a.right.right = TreeNode(6)

    s = Codec1().serialize(a)

    b = Codec1().deserialize(s)


    pass
                
                

                
