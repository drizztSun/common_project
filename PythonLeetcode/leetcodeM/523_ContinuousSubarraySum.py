"""
523. Continuous Subarray Sum

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.



Example 1:

Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:

Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.


Constraints:

The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
"""


class CheckSubarraySumOfMultipleK:

    def doit_array(self, nums: list[int], k: int) -> bool:
        buff, runningtotals = {0: -1}, 0

        for i in range(len(nums)):

            runningtotals += nums[i]

            if k != 0:
                runningtotals %= k

            if runningtotals in buff:
                if i - buff[runningtotals] > 1:
                    return True
            else:
                buff[runningtotals] = i

        return False

    def doit_array_1(self, nums: list[int], k: int) -> bool:
        # Corner case 1  --> n can be 0
        # Corner case 2  --> k can be 0
        #   deal with them together:
        if any([x == y == 0 for x, y in zip(nums, nums[1:])]):
            return True

        if k == 0:
            return False

        # Corner case 3  --> k can be negative
        k = abs(k)

        # Corner case 4  --> sum[nums[:2]] satisfies the condition
        dindex = {0: -1}  # key is (prefixSum % k) ;  value is index
        dsum = {0: 0}  # key is (prefixSum % k) ;  value is prefixSum

        prefixSum = 0
        for i, x in enumerate(nums):
            prefixSum += x
            residual = prefixSum % k
            if residual in dindex:
                if prefixSum - dsum[residual] >= k and i - dindex[residual] >= 2:
                    return True
            else:
                dindex[residual] = i
                dsum[residual] = prefixSum

        return False
