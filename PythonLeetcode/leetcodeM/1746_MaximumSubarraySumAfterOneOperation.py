"""
1746. Maximum Subarray Sum After One Operation


You are given an integer array nums. You must perform exactly one operation where you can replace one element nums[i] with nums[i] * nums[i].

Return the maximum possible subarray sum after exactly one operation. The subarray must be non-empty.



Example 1:

Input: nums = [2,-1,-4,-3]
Output: 17
Explanation: You can perform the operation on index 2 (0-indexed) to make nums = [2,-1,16,-3]. Now, the maximum subarray sum is 2 + -1 + 16 = 17.
Example 2:

Input: nums = [1,-1,1,1,-1,-1,1]
Output: 4
Explanation: You can perform the operation on index 1 (0-indexed) to make nums = [1,1,1,1,-1,-1,1]. Now, the maximum subarray sum is 1 + 1 + 1 + 1 = 4.


Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104


"""


class MaxSumAfterOperation:

    def doit_(self, nums: list) -> int:

        n = len(nums)
        left, total = [0] * n, 0
        for i in range(len(nums)):
            total = max(total + nums[i], nums[i])
            left[i] = max(left[i], total)

        right, total = [0] * n, 0
        for i in reversed(range(len(nums))):
            total = max(total + nums[i], nums[i])
            right[i] = max(right[i], total)

        ans = 0
        for i in range(n):
            ans = max(ans, nums[i] * nums[i] + (left[i - 1] if i > 0 else 0) + (right[i + 1] if i < len(nums) - 1 else 0))
        return ans

    def doit_dp(self, nums: list) -> int:

        dp = [[0 for _ in range(2)] for _ in range(len(nums))]
        dp[0] = [nums[0], nums[0] ** 2]
        max_sum = dp[0][1]

        for j in range(1, len(nums)):
            dp[j][0] = max(dp[j - 1][0] + nums[j], nums[j])
            dp[j][1] = max(dp[j - 1][0] + nums[j] ** 2, dp[j - 1][1] + nums[j], nums[j] ** 2)
            max_sum = max(max_sum, dp[j][1])

        return max_sum