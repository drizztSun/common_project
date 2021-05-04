import os
import math

# leetcode 217. Contains Duplicate
# Given an array of integers, find if the array contains any duplicates. 
# Your function should return true if any value appears at least twice in the array, 
# and it should return false if every element is distinct.
class ContainsDuplicate(object) :
    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        A = set()
        for num in nums:
            if num in A:
                return True
            
            A.add(num)

        return False

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        return len(nums) != len(set(nums))



# leetcode 219. Contains Duplicate II
# Given an array of integers and an integer k, 
# find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] 
# and the absolute difference between i and j is at most k.
class ContainDuplicateII(object):
    
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :rtype: bool
        """
        A = dict()
        for i, num in enumerate(nums):
            if num in A and i - A[num] <= k:
                return True

            A[num] = i

        return False

# leetcode 220. Contains Duplicate III
# Given an array of integers, find out whether there are two distinct indices i and j in the array 
# such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference 
# between i and j is at most k.

class ContainDuplicateIII(object):

    def doit(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        buckets = {}
        for i, num in enumerate(nums):

            bucketNum, offset = (num // t, 1) if t else (num, 0)
            for idx in range(bucketNum - offset, bucketNum + offset + 1):
                if idx in buckets and math.fabs(buckets[idx] - num) <= t:
                    return True
                 
            buckets[bucketNum] = nums[i]

            if len(buckets) > k:
                del buckets[nums[i-k]/t if t else nums[i-k]]

        return False


    def doit2(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        if k <= 0:
            return False

        if t < 0:
            return False

        buckets = dict()  # bucket -> n
        i = j = 0
        while j < len(nums):
            n = nums[j]
            if i == j:
                if t != 0:
                    buckets[n/t] = n
                else:
                    buckets[n] = n
                j += 1
            else:
                if t != 0:
                    for x in [n/t, n/t-1, n/t+1]:
                        if x in buckets and abs(buckets[x] - n) <= t:
                            return True
                    buckets[n/t] = n                
                else:
                    if n in buckets:
                        return True
                    buckets[n] = n
                if j-i == k:
                    if t != 0:
                        del buckets[nums[i]/t]
                    else:
                        del buckets[nums[i]]
                    i += 1
                j += 1
        return False


    # TLE time limit exceeded
    def doit1(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        for i, num in enumerate(nums):
            for j in range(max(i-k, 0), i):
                if math.fabs(nums[j] - nums[i]) <= t:
                    return True
        return False
