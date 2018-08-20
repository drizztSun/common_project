import os
import bisect

# 300. Longest Increasing Subsequence

# Given an unsorted array of integers, find the length of longest increasing subsequence.

# For example,
# Given [10, 9, 2, 5, 3, 7, 101, 18],
# The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. 
# Note that there may be more than one LIS combination, it is only necessary for you to return the length.

# Your algorithm should run in O(n2) complexity.

# Follow up: Could you improve it to O(n log n) time complexity?

# <important> <hard>
class lengthOfLIS(object):

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
            return len(nums)

        def help(D, a):
            s, e = 0, len(D)-1
            while s < e:
                mid = (s + e) // 2
                if D[mid] >= a:
                    e = mid
                else:
                    s = mid+1

            return s
            

        D = [nums[0]]

        for i in range(1, len(nums)):

            if nums[i] > D[-1]:
                D.append(nums[i])

            else:
                D[help(D, nums[i])] = nums[i]

        return len(D)


    # O(n**2) <DP>
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        D = [1 for _ in range(len(nums))]

        for i in range(len(nums)):
            
            for j in range(0, i):
        
                if nums[j] < nums[i]:
                    D[i] = max(D[j]+1, D[i])

            maxV = max(maxV, D[i])

        return maxV
                                        
    # O(n*logn)               
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1: 
            return len(nums)

        lst = [nums[0]]

        for i in range(1, len(nums)):
            if nums[i] > lst[-1]:
                lst.append(nums[i])
                continue

            ii = bisect_left(lst, nums[i])
            lst[ii] = nums[i]

        return len(lst)


if __name__=="__main__":


    res = lengthOfLIS().doit([-2, -1])

    res = lengthOfLIS().doit1([10,9,2,5,3,7,101,18])

    pass
        