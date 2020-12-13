"""
 209. Minimum Size Subarray Sum

 Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s.
 If there isn't one, return 0 instead.

Example:

Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

"""


class MinimumSizeSubarraySum:

    def doit_slidewindow(self, s: int, nums: list) -> int:

        j, total, res = 0, 0, len(nums) + 1

        for i in range(len(nums)):

            total += nums[i]

            while j <= i and total >= s:
                res = min(res, i - j + 1)
                total -= nums[j]
                j += 1

        return 0 if res == len(nums) + 1 else res
