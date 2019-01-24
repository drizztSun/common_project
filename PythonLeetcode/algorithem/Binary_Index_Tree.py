
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
# for example
# E[8] = E[7] + E[6] + a[8] = a[8] + a[7] + a[6] + a[5] + a[4] + a[3] + a[2] + a[1]
# E[6] = a[5] + a[6]
# E[7] = a[7]

# (3)
# e[i] has PreNode and PostNode
# PreNode :  e[i - lowbit(i)]
# PostNode : e[i + lowbit(i)]
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

# leetcode 307 and 308


class RangeSumMutableArray:

    def __init__(self, nums):
        self.__nums = [0] + nums[:]

        self.__e = [0] * len(self.__nums)

        for i in range(1, len(self.__nums)):
            c = self.__nums[i]
            while i < len(self.__e):
                self.__e[i] += c 
                i += (-i) & i

    def __build(self):
        self.__e = self.__nums
        for i in range(1, len(self.__nums)):
            k = i
            while i > 0:
                i -= (-i) & i
                self.__e[k] += self.__e[i]
                

    def update(self, i, n):
        diff = n - self.__nums[i+1]
        self.__nums[i+1], k = n, i+1

        while k < len(self.__e):
            self.__e[k] += diff
            k += (-k) & k


    def sumRange(self, i, j):
        res, j = 0, j + 1

        while j > 0:
            res += self.__e[j]
            j -= (-j) & j

        while i > 0:
            res -= self.__e[i]
            i -= (-i) & i

        return res


if __name__ == "__main__":
    
    o = RangeSumMutableArray([1, 3, 5])
    
    o._RangeSumMutableArray__build()
    res = o.sumRange(0, 2)

    o.update(1, 2)

    res = o.sumRange(0, 2)


    obj = RangeSumMutableArray([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    res = obj.sumRange(3, 8)

    res = obj.update(2, 10)
