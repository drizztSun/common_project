"""
152. Maximum Product Subarray

Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
"""


class MaxProduct:

    def doit_dp(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_v, min_v = 1, 1
        r = nums[0]

        for c in nums:

            if c < 0:
                max_v, min_v = min_v, max_v

            max_v = max(max_v*c, c)
            min_v = min(min_v*c, c)

            r = max(r, max_v)

        return r

    def doit_dp_1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        reverse = nums[::-1]

        for i in range(1, len(nums)):
            nums[i] *= nums[i - 1] or 1
            reverse[i] *= reverse[i - 1] or 1

        # print nums,reverse

        return max(nums + reverse)




