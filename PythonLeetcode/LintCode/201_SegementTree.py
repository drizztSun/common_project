# 201 Segement Tree

# The structure of Segment Tree is a binary tree which each node has two attributes start and end denote an segment / interval.
# start and end are both integers, they should be assigned in following rules:
# The root's start and end is given by build method.
# The left child of node A has start=A.left, end=(A.left + A.right) / 2.
# The right child of node A has start=(A.left + A.right) / 2 + 1, end=A.right.
# if start equals to end, there will be no children for this node.
# Implement a build method with two parameters start and end, so that we can create a corresponding segment tree with every node has the correct start and end value, return the root of this segment tree.


# Clarification
# Segment Tree (a.k.a Interval Tree) is an advanced data structure which can support queries like:

# which of these intervals contain a given point
# which of these points are in a given interval
# See wiki:
# Segment Tree
# Interval Tree

# Example
# Given start=0, end=3. The segment tree will be:

#               [0,  3]
#             /        \
#      [0,  1]           [2, 3]
#      /     \           /     \
#   [0, 0]  [1, 1]     [2, 2]  [3, 3]
# Given start=1, end=6. The segment tree will be:

#               [1,  6]
#             /        \
#      [1,  3]           [4,  6]
#      /     \           /     \
#   [1, 2]  [3,3]     [4, 5]   [6,6]
#   /    \           /     \
#[1,1]   [2,2]     [4,4]   [5,5]

class SegmentTreeNode:
    def __init__(self, start, end, max=0):
        self.start, self.end = start, end
        self.left, self.right = None, None

        self.max = max

class SegmentTreeBuilder:
    """
    @param: start: start value.
    @param: end: end value.
    @return: The root of Segment Tree.
    """
    def doit(self, start, end) :

        def build(s, e):
            if s > e:
                return None
        
            if s == e:
                return SegmentTreeNode(s, e)

            A = SegmentTreeNode(s, e)
            mid = (s + e) // 2

            A.left = build(s, mid)
            A.right = build(mid + 1, e)

            return A

        return build(start, end)

# 
class SegmentTreeMaxBuilder:
    def doit(self, start, end, A):
        
        def build(s, e, A):
            if e < s:
                return None

            cur = SegmentTreeNode(s, e, A[s])
            if s == e:
                return cur

            mid = (s + e) // 2
            cur.left = build(s, mid, A)
            cur.right = build(mid + 1, e, A)
            cur.max = max(cur.left.max, cur.right.max)

            return cur
    
        return build(start, end, A)

# 202. Segment Tree Query
# For an integer array (index from 0 to n-1, where n is the size of this array), in the corresponding SegmentTree, 
# each node stores an extra attribute max to denote the maximum number in the interval of the array (index from start to end).
# Design a query method with three parameters root, start and end, 
# find the maximum number in the interval [start, end] by the given root of segment tree.

# Example
# For array [1, 4, 2, 3], the corresponding Segment Tree is:

#                  [0, 3, max=4]
#                 /             \
#          [0,1,max=4]        [2,3,max=3]
#          /         \        /         \
#   [0,0,max=1] [1,1,max=4] [2,2,max=2], [3,3,max=3]
# query(root, 1, 1), return 4
# query(root, 1, 2), return 4
# query(root, 2, 3), return 3
# query(root, 0, 2), return 4

class SegmentTreeQuery:
    """
    @param root: The root of segment tree.
    @param start: start value.
    @param end: end value.
    @return: The maximum number in the interval [start, end]
    """
    def doit(self, root, start, end):
        # write your code here
        def search(node, start, end):
            if start <= node.start and node.end <= end:
                return node.max

            ans = float('inf')
            mid = (node.start + node.end) // 2
            if mid >= start:
                ans = max(ans, search(node.left, start, end))
    
            if end >= mid + 1:
                ans = max(ans, search(node.right, start, end))

            return ans

        return search(root, start, end)
          

# 203 Segment Tree Modify
# For a Maximum Segment Tree, which each node has an extra value max to store the maximum value in this node's interval.

# Implement a modify function with three parameter root, 
# index and value to change the node's value with [start, end] = [index, index] to the new given value. 
# Make sure after this change, every node in segment tree still has the max attribute with the correct value.

# Example
# For segment tree:

#                      [1, 4, max=3]
#                    /                \
#        [1, 2, max=2]                [3, 4, max=3]
#       /              \             /             \
# [1, 1, max=2], [2, 2, max=1], [3, 3, max=0], [4, 4, max=3]
# if call modify(root, 2, 4), we can get:

#                      [1, 4, max=4]
#                    /                \
#        [1, 2, max=4]                [3, 4, max=3]
#       /              \             /             \
# [1, 1, max=2], [2, 2, max=4], [3, 3, max=0], [4, 4, max=3]
# or call modify(root, 4, 0), we can get:

#                      [1, 4, max=2]
#                    /                \
#        [1, 2, max=2]                [3, 4, max=0]
#       /              \             /             \
# [1, 1, max=2], [2, 2, max=1], [3, 3, max=0], [4, 4, max=0]
# Challenge
# Do it in O(h) time, h is the height of the segment tree.

class SegmentTreeModify:

    def doit1(self, root, index, value):
        """
        @param: root: The root of segment tree.
        @param: index: index.
        @param: value: value
        @return: 
        """
        def modify(node, index, val):

            if node.start == node.end == index:
                node.max = val
                return val

            mid = (node.start + node.end) // 2

            if mid >= index and node.left:
                b = modify(node.left, index, val)
                node.max = max(b, b if not node.right else node.right.max)
            else:
                b = modify(node.right, index, val)
                node.max = max(b, b if not node.left else node.left.max)

            return node.max       

        modify(root, index, value)


    def doit(self, root, index, value):
        """
        @param: root: The root of segment tree.
        @param: index: index.
        @param: value: value
        @return: 
        """
        def modify(node, index, value):
            if node.start == node.end == index:
                node.max = value
                return

            mid = (node.start + node.end) // 2

            if mid >= index:
                modify(node.left, index, value)
            else:
                modify(node.right, index, value)

            node.max = max(node.left.max, node.right.max)
            
        modify(root, index, value)


if __name__== "__main__":


    A = [1, 4, 2, 3]
    
    root = SegmentTreeMaxBuilder().doit(A)

    res = SegmentTreeQuery().doit(root, 2, 3)    

    res = SegmentTreeQuery().doit(root, 1, 3)    

    res = SegmentTreeQuery().doit(root, 1, 2)    

    res = SegmentTreeModify().doit(root, 2, 4)

    pass
            