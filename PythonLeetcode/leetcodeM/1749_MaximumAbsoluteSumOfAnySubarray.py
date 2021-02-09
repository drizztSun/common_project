"""
1749. Maximum Absolute Sum of Any Subarray

You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.


Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.


Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104


"""


class MaxAbsoluteSum:

    def doit_max(self, nums: list) -> int:

        ret, mx, mn = 0, 0, 0

        for c in nums:
            mx = max(mx + c, c)
            mn = min(mn + c, c)

            ret = max(ret, abs(mx))
            ret = max(ret, abs(mn))

        return ret

    def doit_slidingwindow(self, nums: list) -> int:

        ans, positive, negetive = 0, 0, 0
        for i in range(len(nums)):

            if positive + nums[i] < nums[i]:
                positive = 0

            if negetive + nums[i] > nums[i]:
                negetive = 0

            positive += nums[i]
            negetive += nums[i]

            ans = max(ans, positive, abs(negetive))

        return ans

    def doit_presum(self, nums):

        prefix, mx, mn = 0, 0, 0

        for c in nums:
            prefix += c
            mx = max(mx, prefix)
            mn = min(mn, prefix)

        return mx - mn

