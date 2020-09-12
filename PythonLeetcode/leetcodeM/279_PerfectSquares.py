"""
279. Perfect Squares

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
"""

from math import sqrt


class NumPerfectSquares:

    def doit_dp(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n < 2:
            return n
        lst = []
        i = 1
        while i * i <= n:
            lst.append(i * i)
            i += 1

        cnt = 0
        toCheck = {n}
        while toCheck:
            cnt += 1
            temp = set()
            for x in toCheck:
                for y in lst:
                    if x == y:
                        return cnt
                    if x < y:
                        break
                    temp.add(x - y)

            toCheck = temp

        return cnt

    def doit_dp_1(self, n):
        """
        :type n: int
        :rtype: int
        """
        if int(sqrt(n)) ** 2 == n:
            return 1

        for j in range(int(sqrt(n)) + 1):
            if int(sqrt(n - j * j)) ** 2 == n - j * j:
                return 2

        # every num is 4*n + 4, so many 2*2
        while n % 4 == 0:
            n >>= 2

        if n % 8 == 7:
            return 4
        return 3

    def doit_dp_2(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [0]
        while len(dp) <= n:
            dp += min(dp[-i*i] for i in range(1, int(len(dp)**0.5+1))) + 1,
        return dp[n]