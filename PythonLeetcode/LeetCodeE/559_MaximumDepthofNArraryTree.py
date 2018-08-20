# 559. Maximum Depth of N-ary Tree

# Given a n-ary tree, find its maximum depth.

# The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

# For example, given a 3-ary tree:

 


 
# We should return its max depth, which is 3.

# Note:

# The depth of the tree is at most 1000.
# The total number of nodes is at most 5000.
 

# Definition for a Node.
class Node(object):
    def __init__(self, val, children):
        self.val = val
        self.children = children


class MaxDepthNArrayTree(object):

    def search(self, root):
        """
        :type root: Node
        :rtype: int
        """
        def search(node, depth):
        
            if len(node.children) == 0:
                return depth
            
            maxv = 0
            for c in node.children:
                maxv = max(maxv, search(c, depth + 1))

            return maxv

        if not root:
            return 0
        
        return search(root, 1)


    def search(self, root):
        """
        :type root: Node
        :rtype: int
        """
        if not root:
            return 0

        from colections import deque
        st = deque()
        st.append((root, 1))
        depth = 0    
    
        while st:
            length = len(st)        
            for _ in range(length):

                current, depth = st.popleft()
                if current:
                    for n in current.children:
                        st.append((n, depth + 1))

        return depth
        
          
                


if __name__ == "__main__":

    pass

