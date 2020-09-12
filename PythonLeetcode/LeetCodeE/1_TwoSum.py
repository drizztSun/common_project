"""
1. Two Sum

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.



Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

"""


class TwoSum:

    def doit(self, nums, target):

        buf = {}
        for i in range(len(nums)):
            if target - nums[i] in buf:
                return [buf[target - nums[i]], i]
            buf[nums[i]] = i

        return []

    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        result = []
        i = 0
        while i < len(nums):
            j = 0
            while j < len(nums):
                if nums[i] + nums[j] == target and j != i:
                    if i not in result:
                        result.append(i)
                    if j not in result:
                        result.append(j)
                j += 1
            i += 1
        return result