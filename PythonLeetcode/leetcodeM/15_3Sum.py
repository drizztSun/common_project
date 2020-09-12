"""
15. 3Sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.



Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
"""


class ThreeSum:
    def doit(self, nums):

        if len(nums) < 3:
            return []

        buf = {nums[i]:i for i in range(len(nums))}
        seen = set()
        for i in range(len(nums)):

            for j in range(i+1, len(nums)):

                third = 0 - nums[i] - nums[j]
                if third in buf and buf[third] not in (i, j):
                    c = sorted([nums[i], nums[j], third])
                    seen.add(tuple(c))

        return [list(c) for c in seen]

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = []
        nums.sort()

        for i, a in enumerate(nums):
            # meet bigger than 0, on left side, the rest is greater than 0. drop
            if a > 0:
                break

            # The all rest is the same, break
            if i > 0 and a == nums[i - 1]:
                continue

            l, r = i + 1, len(nums) - 1
            while l < r:
                threeSum = a + nums[l] + nums[r]
                if threeSum > 0:
                    r -= 1
                elif threeSum < 0:
                    l += 1
                else:
                    res.append([a, nums[l], nums[r]])
                    l += 1
                    r -= 1
                    while nums[l] == nums[l - 1] and l < r:
                        l += 1
                    while nums[r] == nums[r + 1] and l < r:
                        r -= 1

        return res
