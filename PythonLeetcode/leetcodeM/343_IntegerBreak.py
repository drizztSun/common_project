"""
343. Integer Break

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers.
Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
Note: You may assume that n is not less than 2 and not larger than 58.

"""


class IntegerBreak:

    def doit_dp(self, n: int) -> int:

        dp = [0 for _ in range(n + 1)]
        dp[2] = 1

        for i in range(3, n + 1):

            for j in range(1, i):
                dp[i] = max(dp[i], j * (i - j), j * dp[i - j])

        return dp[n]

    def doit_dp_1(self, n: int) -> int:
        if n == 2:
            return 1
        if n == 3:
            return 2
        if n == 4:
            return 4

        ans = (3 ** (n // 3))
        if n % 3 == 1:
            return ans // 3 * 4
        if n % 3 == 2:
            return ans * 2
        return ans

