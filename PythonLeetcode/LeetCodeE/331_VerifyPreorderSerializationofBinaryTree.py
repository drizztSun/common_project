


# 331. Verify Preorder Serialization of a Binary Tree

# One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. 
# If it is a null node, we record using a sentinel value such as #.
#      _9_
#     /   \
#    3     2
#   / \   / \
#  4   1  #  6
# / \ / \   / \
# # # # #   # #
# For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

# Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

# Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

# You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

# Example 1:
# "9,3,4,#,#,1,#,#,2,#,6,#,#"
# Return true

# Example 2:
# "1,#"
# Return false

# Example 3:
# "9,#,#,1"
# Return false



class isValidSerialization(object):
    def doit(self, preorder):
        """
        :type preorder: str
        :rtype: bool
        """
        if len(preorder) < 1:
            return True
        
        i = 0 
        preorder = preorder.split(',')
        buff = [] 
        while i < len(preorder):

            if preorder[i] != '#':
                buff.append(preorder[i])
            else:
                while len(buff) > 1 and buff[-1] == '#' and buff[-2] != '#':
                    buff.pop()
                    buff.pop()
                buff.append('#')
            i += 1

        return len(buff) == 1 and buff[0] == "#"            


# Some used stack. Some used the depth of a stack. Here I use a different perspective. 
# In a binary tree, if we consider null as leaves, then

# all non-null node provides 2 outdegree and 1 indegree (2 children and 1 parent), except root
# all null node provides 0 outdegree and 1 indegree (0 child and 1 parent).
# Suppose we try to build this tree. During building, we record the difference between out degree and in degree diff = outdegree - indegree. 
# When the next node comes, we then decrease diff by 1, because the node provides an in degree. 
# If the node is not null, we increase diff by 2, because it provides two out degrees. 
# If a serialization is correct, diff should never be negative and diff will be zero when finished.
        
    def doit1(self, preorder):
        """
        :type preorder: str
        :rtype: bool
        """
        diff = 1
        for i in preorder.split(','):
            diff -= 1
            if diff < 0:
                return False
            if i != '#':
                diff += 2

        return diff == 0




if __name__=="__main__":


    res = isValidSerialization().doit("9,#,#,1")

    res = isValidSerialization().doit("1,#")

    res = isValidSerialization().doit("9,3,4,#,#,1,#,#,2,#,6,#,#")

    pass