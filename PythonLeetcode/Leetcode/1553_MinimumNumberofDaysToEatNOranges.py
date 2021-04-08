"""
1553. Minimum Number of Days to Eat N Oranges

There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:

Eat one orange.
If the number of remaining oranges (n) is divisible by 2 then you can eat  n/2 oranges.
If the number of remaining oranges (n) is divisible by 3 then you can eat  2*(n/3) oranges.
You can only choose one of the actions per day.

Return the minimum number of days to eat n oranges.



Example 1:

Input: n = 10
Output: 4
Explanation: You have 10 oranges.
Day 1: Eat 1 orange,  10 - 1 = 9.
Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1.
Day 4: Eat the last orange  1 - 1  = 0.
You need at least 4 days to eat the 10 oranges.
Example 2:

Input: n = 6
Output: 3
Explanation: You have 6 oranges.
Day 1: Eat 3 oranges, 6 - 6/2 = 6 - 3 = 3. (Since 6 is divisible by 2).
Day 2: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. (Since 3 is divisible by 3)
Day 3: Eat the last orange  1 - 1  = 0.
You need at least 3 days to eat the 6 oranges.
Example 3:

Input: n = 1
Output: 1
Example 4:

Input: n = 56
Output: 6


Constraints:

1 <= n <= 2*10^9

"""


class MinDays:


    """
        Solution 3: Optimized DP + Greedy

        ALways eat one at a time is definitely not the best option.
        We can eat k in k steps such that n-k is a multiple of 2 or 3 such that we can eat 1/2 or 2/3 in one step.
        dp(i) := min stesps to eat i oragnes.

        dp(n) = 1 + min{n%2 + dp(n/2), n%3 + dp(n/3)}

        Time complexity: O(logn)^2
        Space complexity: O(logn)^2

        Never take more than 2 consecutive -1 operations.
        Proog: suppose we need 3 consecuitve -1 operations to reach the optimal solution.

        days(n) -> days(n-3) in 3 steps

        Option 1: /2 => we reach days((n-3)/2) = days((n-1)/2 -1) in (3 + 1) = 4 steps
        However, days(n) -> days(n-1) -> days((n-1)/2) -> days((n-1)/2-1) in 3 steps

        Option 2: /3 => we reach days((n-3)/3) = days(n/3-1) in (3+1) = 4 steps
        Hpwever, days(n) -> days(n/3) -> days(n/3 -1) in 2 steps

        This can be extended to k consecutive -1 operations (k>=3)
    """
    def doit_topdown_dp(self, n: int) -> int:

        from functools import lru_cache

        @lru_cache(None)
        def search(num):
            if num < 2:
                return num

            return 1 + min(num % 2 + search(num // 2), num % 3 + search(num // 3))

        return search(n)


