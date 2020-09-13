"""
303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3


Constraints:

You may assume that the array does not change.
There are many calls to sumRange function.
0 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5
0 <= i <= j < nums.length
"""


class NumArray(object):

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self._m = len(nums)
        self._mNums = [0 for x in range(self._m + 1)]
        for i in range(1, self._m + 1):
            self._mNums[i] = self._mNums[i - 1] + nums[i - 1]

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        if i > j or j >= self._m:
            return 0

        return self._mNums[j + 1] - self._mNums[i]
