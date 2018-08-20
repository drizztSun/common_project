import os


# 249. Count of Smaller Number before itself
# Give you an integer array (index from 0 to n-1, where n is the size of this array, data value from 0 to 10000) . 
# For each element Ai in the array, count the number of element before this element Ai is smaller than it and return count number array.

class SegmentTreeCounterNode(object):
    
    def __init__(self, start, end, count = 0):

        self.start, self.end = start, end
        self.count = count

        self.left, self.right = None, None


class SegmentTreeCounter:

    def __init__(self, n):

        self.root = self.build(n)


    def build(self, n):

        def forge(s, e):

            A = SegmentTreeCounterNode(s, e)

            if s == e:
                return A

            mid = (s + e) // 2

            A.left = forge(s, mid)
            A.right = forge(mid+1, e)

            A.count = A.left.count + A.right.count

            return A

        return forge(0, n)


    def query(self, start, end):

        def search(node, start, end):
            if start <= node.start and node.end <= end:
                return node.count

            mid = (node.start + node.end) // 2
        
            total = 0
            if mid >= start:
                total += search(node.left, start, end)

            if mid+1 <= end:
                total += search(node.right, start, end)

            return total

        if not self.root or end < start:
            return 0

        return search(self.root, start, end)


    def insert(self, index):

        def insertHelper(node, index):
            if node.start == node.end == index:
                node.count += 1
                return

            mid = (node.start + node.end) // 2
            if mid >= index:
                insertHelper(node.left, index)
            else:
                insertHelper(node.right, index)

            node.count = node.left.count + node.right.count

        insertHelper(self.root, index)            
                
                
            

class CountOfSmallerNumberII:
    """
    @param: A: an integer array
    @return: A list of integers includes the index of the first number and the index of the last number
    """
    def doit(self, A):
        # write your code here

        segmentTreeCounter = SegmentTreeCounter(10000)

        B = [0 for _ in range(len(A))]

        for i in range(1, len(A)):
            
            segmentTreeCounter.insert(A[i-1])

            B[i] = segmentTreeCounter.query(0, A[i]-1)

        return B



# 247. Segment Tree Query II

# For an array, we can build a SegmentTree for it, each node stores an extra attribute count to denote the number of elements in the the array which value is between interval start and end. 
# (The array may not fully filled by elements)

# Design a query method with three parameters root, start and end, find the number of elements in the in array's interval [start, end] by the given root of value SegmentTree.

class SegmentTreeQueryII:

    def query(self, root, start, end):
        """
        @param: root: The root of segment tree.
        @param: start: start value.
        @param: end: end value.
        @return: The count number in the interval [start, end]
        """
        # write your code here
        def queryHelper(node, s, e):

            if s > node.end or e < node.start:
                return 0
            
            if s <= node.start and node.end <= e:
                return node.count

            mid = (node.start + node.end) // 2
            total = 0

            if mid >= s :
                total += queryHelper(node.left, s, e)

            if mid + 1 <= e:
                total += queryHelper(node.right, s, e)

            return total
            
        if not root:
            return 0

        return queryHelper(root, start, end)


if __name__=="__main__":


    
    # B = CountOfSmallerNumberII().doit([1, 2, 7, 8, 5])

    B = CountOfSmallerNumberII().doit([73,82,74,12,25,0,33,46,79,90,6,97,18,84,34,54,64,5,54,44,74,95,90,24,70,94,12,41,79,88,48,82,89,100,33,3,23,21,90,50,26,3,4,21,67,24,59,62,9,78,60,40,4,40,7,5,54,38,68,66])
    

    pass