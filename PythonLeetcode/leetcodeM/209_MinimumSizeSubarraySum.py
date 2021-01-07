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

    def doit_slidingwindow(self, s: int, nums: list) -> int:

        j, total, res = 0, 0, len(nums) + 1

        for i in range(len(nums)):

            total += nums[i]

            while j <= i and total >= s:
                res = min(res, i - j + 1)
                total -= nums[j]
                j += 1

        return 0 if res == len(nums) + 1 else res

    def doit_binary_search(sel, s: int, nums: list) -> int:

        n = len(nums)
        presum = [0] * (n+1)
        for i in range(n):
            presum[i+1] = presum[i] + nums[i]

        res = float('inf')
        for i in range(len(presum)):

            target = presum[i] + s
            left, right = 0, len(presum)
            
            while left < right:
                mid = (left + right) // 2
                if presum[mid] >= target:
                    right = mid
                else:
                    left = mid + 1

            if left != len(presum):
                res = min(res, left - i)

        return 0 if res == float('inf') else res

if __name__ == '__main__':

    MinimumSizeSubarraySum().doit_binary_search(15, [1,2,3,4,5])