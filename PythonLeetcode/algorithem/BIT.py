
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
