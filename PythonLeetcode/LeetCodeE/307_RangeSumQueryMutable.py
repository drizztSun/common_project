

# 307. Range Sum Query - Mutable

# Given an integer array nums, find the sum of the elements between indices i and j (i ? j), inclusive.
# The update(i, val) function modifies nums by updating the element at index i to val.

# Example:
# Given nums = [1, 3, 5]

# sumRange(0, 2) -> 9
# update(1, 2)
# sumRange(0, 2) -> 8


# <hard> <important>
class SegmentTreeSumNode:
        
    def __init__(self, start, end, sum=0):

        self.start, self.end = start, end

        self.sum = sum
    
        self.right, self.left = None, None


class SegementTreeSum:

    def __init__(self, A):

        self.root = self.build(A) if A else None

    def build(self, A):

        def forge(A, s, e):
            
            a = SegmentTreeSumNode(s, e)
            if s == e:
                a.sum = A[s]
                return a
        
            mid = (s + e) // 2

            a.left = forge(A, s, mid)
            a.right = forge(A, mid+1, e)

            a.sum = a.left.sum + a.right.sum
            return a

        return forge(A, 0, len(A)-1)

    # O(logN)
    def update(self, idx, val):

        def updateHelper(node, idx, val):

            if node.start == node.end == idx:
                node.sum = val
                return

            mid = (node.start + node.end) // 2

            if mid >= idx:
                updateHelper(node.left, idx, val)

            elif mid < idx:
                updateHelper(node.right, idx, val)

            node.sum = node.left.sum + node.right.sum
        
        if self.root:
            updateHelper(self.root, idx, val)
              
    # O(logN)
    def query(self, start, end):

        def queryHelper(node, s, e):

            if s <= node.start and node.end <= e:
                return node.sum

            mid = (node.start + node.end) // 2

            sum = 0
            if s <= mid:
                sum += queryHelper(node.left, s, e)

            if e >= mid+1:
                sum += queryHelper(node.right, s, e)

            return sum
        
        if not self.root:
            return 0

        return queryHelper(self.root, start, end)
         

class NumArray:

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.sgmnTree = SegementTreeSum(nums)

    def update(self, i, val):
        """
        :type i: int
        :type val: int
        :rtype: void
        """
        self.sgmnTree.update(i, val)

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        return self.sgmnTree.query(i, j)
        



# normal way, O(n)
class NumArrayOn(object):
    def __init__(self, nums):
        self.update = nums.__setitem__
        self.sumRange = lambda i, j: sum(nums[i:j+1])


class NumArrayBiTree:

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.bitree = None
        if nums is None: 
            return

        n = len(nums)
        self.nums = [0] * n
        self.length = n
        self.bitree = [0] * (n + 1)

        for i in range(n):
            self.update_helper(i, nums[i])
            self.nums[i] = nums[i]
    
    def update_helper(self, i, val):

        diff = val - self.nums[i]
        self.nums[i] = val
        i = i + 1

        while i <= self.length:
            self.bitree[i] += diff
            i += i & (-i)
            

    def update(self, i, val):
        """
        :type i: int
        :type val: int
        :rtype: void
        """
        self.update_helper(i, val)

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        if i > j: 
            return 0
        
        return self.sum_range_helper(j) - self.sum_range_helper(i - 1)

    def sum_range_helper(self, i):
        i += 1
        tmp_sum = 0

        while i > 0:
            tmp_sum += self.bitree[i]
            i -= i & (-i)

        return tmp_sum


# Binary Indexed Tree 
# https://www.cnblogs.com/xudong-bupt/p/3484080.html
# Use self.c to represent Binary Indexed Tree. 

# Section sums(E) are stored in E[1..len(nums)]. 
# x & -x is lowbit function, which will return x s rightmost bit 1, e.g.
# lowbit(7) = 1, lowbit(20) = 4.

# (1) and (2)
# lowbit(i) == ((i-1) ^ i & i) 
# or
# lowbit(i) == i & -i

# E[i] = A[i]  if i % 2 == 1
# E[i] = A[i] + A[i-1] + ...... + A[i - 2^k + 1]  

# (3)
# e[i] has PreNode and PostNode
# PreNode :  e[i - lowbit(i)]
# PostNode : e[i + lowbit(i)]
# E[8] = 
# 
# E is sum of A
# E[1] = nums[0]
# E[2] = nums[0] + nums[1]
# E[3] = nums[2]
# E[4] = nums[0] + nums[1] + nums[2] + nums[3]
# E[5] = nums[4]
# E[6] = nums[4] + nums[5]
# E[7] = nums[6]
# E[8] = nums[0] + nums[1] + nums[2] + nums[3] + nums[4] + nums[5] + nums[6] + nums[7]
#
#

# <BIT>
class NumArrayBiTree:

    def __init__(self, nums):

        self.nums = nums
        self.n = len(nums)
        self.c = [0] * (len(nums) + 1)

        for i in range(self.n):
            k = i + 1
            while k <= self.n: 
                self.c[k] += nums[i]
                k +=  k & (-k)
                

    def update(self, i, val):
        diff = val - self.nums[i]
        self.nums[i] = val
        i += 1

        while i < len(self.c):
            
            self.c[i] += diff
            
            i += i & (-i)

    def sumRange(self, i, j):
        
        res, j = 0, j + 1

        while j :
            res += self.c[j]
            j -= j & (-j)

        while i:
            res -= self.c[i]
            i -= i & (-i)

        return res





class NumArrayBiTree1:

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.nums_ = nums
        self.e_ = [0 for x in range(len(nums) + 1)]


        for i in range(len(nums)):
            k = i + 1
            while k < len(self.e_):
                self.e_[k] += nums[i]
                k += ((k-1) ^ k) & k

    def update(self, i, val):
        """
        :type i: int
        :type val: int
        :rtype: void
        """
        diff = val - self.nums_[i] 
        self.nums_[i] = val
        k = i + 1
        
        while k < len(self.e_):
            self.e_[k] += diff
            k += ((k-1) ^ k) & k

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        res = 0
        j += 1
        while j > 0:
            res += self.e_[j]
            lowbit = ((j - 1) ^ j) & j
            j -= lowbit
        
        while i > 0:
            res -= self.e_[i]
            lowbit = ((i - 1) ^ i) & i
            i -= lowbit

        return res


if __name__=="__main__":


    obj = NumArrayBiTree([1, 3, 5])
    
    res = obj.sumRange(0, 2)

    obj.update(1, 2)

    res = obj.sumRange(0, 2)


    # Your NumArray object will be instantiated and called as such:
    obj = NumArrayBiTree([1, 3, 5, 7, 9])

    res = obj.sumRange(0, 4)  # 

    obj.update(1, 2)

    res = obj.sumRange(0, 4)

    obj = NumArrayBiTree([0, 9, 5, 7, 3])
    
    res = obj.sumRange(4, 4)

    pass