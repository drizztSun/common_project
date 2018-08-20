import os


# 205. Interval Minimum Number
# Given an integer array (index from 0 to n-1, where n is the size of this array), and an query list. 
# Each query has two integers [start, end]. For each query, calculate the minimum number between index 
# start and end in the given array, return the result list.


class SegmentTreeMinimumNode:
    def __init__(self, start, end):
        self.start, self.end = start, end
        self.minimum = 0



class SegmentTreeMinimum:

    def __init__(self, A):
        
        self.root = self.build(A)

    def build(self, A):
        if not A:
            return None

        def forge(A, s, e):
            
            a = SegmentTreeMinimumNode(s, e)

            if s == e:
                a.minimum = A[s]
                return a
            mid = (s + e) // 2
            a.left = forge(A, s, mid)
            a.right = forge(A, mid+1, e)

            a.minimum = min(a.left.minimum, a.right.minimum)

            return a

        return forge(A, 0, len(A)-1)


    def query(self, start, end):

        def queryHelper(node, s, e):

            if s <= node.start and node.end <= e:
                return node.minimum

            mid = (node.start + node.end) // 2

            ans = 10000000
            if mid >= s:
                ans = min(ans, queryHelper(node.left, s, e))

            if mid + 1 <= e:
                ans = min(ans, queryHelper(node.right, s, e))
    
            return ans

        return queryHelper(self.root, start, end)



# Definition of Interval.
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end


class IntervalMinNumber:

    def doit(self, A, queries):
        """
        @param: A: An integer array
        @param: queries: An query list
        @return: The result list
        """
        a = SegmentTreeMinimum(A)
        b = []

        for c in queries:
            b.append(a.query(c.start, c.end))

        return b
        
        
if __name__=="__main__":

    a = [1, 2, 7, 8, 5]

    c = []
    c.append(Interval(1, 2))
    c.append(Interval(0, 4))
    c.append(Interval(2, 4))

    
    b = IntervalMinNumber().doit(a, c)



    pass
