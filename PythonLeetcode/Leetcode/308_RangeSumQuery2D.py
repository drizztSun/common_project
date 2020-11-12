"""
# 307 Range Sum Query Mutable


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
"""


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
                k += k & (-k)

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

"""
308 Range Sum Query 2D Mutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.
"""


class NumArray2D(object):

    def __init__(self, nums):

        self.nums_ = nums

        m, n = len(nums), len(nums[0])

        self.D_ = [[0 for i in range(n+1)] for _ in range(m)]

        for i in range(m):
            for j in range(n):
                k = j + 1
                while k < len(self.D_[i]): 
                    self.D_[i][k] += self.nums_[i][j]
                    k += -k & k

    def update(self, i, j, val):
        """
        :type i: int
        :type val: int
        :rtype: void
        """
        diff = val - self.nums_[i][j] 
        k = j + 1
        while k < len(self.D_[i]):
            self.D_[i][k] += diff
            k += -k & k

        self.nums_[i][j] = val  

    def sumRegion(self, x1, y1, x2, y2):

        result = 0

        for i in range(x1, x2 + 1):
            line = 0
            high, low = y2 + 1, y1

            while high > 0:
                line += self.D_[i][high]
                high -= -high & high

            while low > 0:
                line -= self.D_[i][low]
                low -= -low & low
        
            result += line

        return result 


if __name__ == "__main__":

    obj = NumArrayBiTree([1, 3, 5])
    
    res = obj.sumRange(0, 2)

    obj.update(1, 2)

    res = obj.sumRange(0, 2)

    matrix = [
            [3, 0, 1, 4, 2],
            [5, 6, 3, 2, 1],
            [1, 2, 0, 1, 5],
            [4, 1, 0, 1, 7],
            [1, 0, 3, 0, 5]
        ]

    obj = NumArray2D(matrix)

    res = obj.sumRegion(2, 1, 4, 3) # 8
    
    obj.update(3, 2, 2)

    res = obj.sumRegion(2, 1, 4, 3) # 10ß