# 207. Interval Sum II
# Given an integer array in the construct method, implement two methods query(start, end) and modify(index, value):

# For query(start, end), return the sum from index start to index end in the given array.
# For modify(index, value), modify the number in the given index to value

class SegmentTreeSumNode:
    def __init__(self, start, end, sum=0):
        self.start, self.end = start, end
        self.left, self.right = None, None
        self.sum = sum

class IntervalSum:

    def __init__(self, A):
        self.A = A
        self.root = self.build(A)


    def build(self, A):

        def buildNode(A, s, e):
            
            node = SegmentTreeSumNode(s, e)
    
            if s == e:
                node.sum = A[s]
            else:
                mid = (s + e) // 2

                node.left = buildNode(A, s, mid)
                node.right = buildNode(A, mid + 1, e)

                node.sum = node.left.sum + node.right.sum

            return node

        if not A:
            return None

        return buildNode(A, 0, len(A)-1)


    def query(self, start, end):
        """
        @param: start: An integer
        @param: end: An integer
        @return: The sum from start to end
        """
        def queryHelper(node, s, e):
            
            if s <= node.start and node.end <= e:
                return node.sum

            mid = (node.start + node.end) // 2
        
            ls, rs = 0, 0
            if mid >= s:
                ls = queryHelper(node.left, s, e)

            if mid + 1 <= e:
                rs = queryHelper(node.right, s, e)

            return ls + rs

        if not self.root:
            return 0

        return queryHelper(self.root, start, end)


    def modify(self, index, value):
        """
        @param: index: An integer
        @param: value: An integer
        @return: nothing
        """
        def modifyHelper(node, index, value):
            if node.start == node.end == index:
                node.sum = value
                return

            mid = (node.start + node.end) // 2
    
            if mid >= index:

                modifyHelper(node.left, index, value)

            else:
                
                modifyHelper(node.right, index, value)


            node.sum = node.left.sum + node.right.sum


        modifyHelper(self.root, index, value)





if __name__=="__main__":

    A = [1,2,7,8,5]

    
    obj = IntervalSum(A)

    res = obj.query(0, 2)  # 10

    obj.modify(0, 4) 

    res = obj.query(0, 1)

    obj.modify(2, 1)

    res = obj.query(2, 4)



    pass
