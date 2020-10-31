"""
829. Consecutive Numbers Sum

# Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?

# Example 1:

# Input: 5
# Output: 2
# Explanation: 5 = 5 = 2 + 3

# Example 2:

# Input: 9
# Output: 3
# Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
# Example 3:

# Input: 15
# Output: 4
# Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5

"""


class ConsecutiveNumbersSum:


    """
    # N = x + (x+1) +(x+2) + (x+3)+ ... + y
    # => N = (x+y) * (y-x+1) / 2
    # => 2 * N = (x+y) * (y-x+1)
    # x     |odd  |even |odd  |even
    # y     |even |odd  |odd  |even
    # y-x+1 |even |even |odd  |odd
    # y+x   |odd  |odd  |even |even
    # 2 * N |even |even |even |even
    # => let's say i = x+y, j = y-x+1, as long as not (i is odd and j is odd) or not (i is even and j is even)
    # we have one more way to express N as consecutive numbers sum
    """
    def doit(self, N):
        """
        :type N: int
        :rtype: int
        """
        ans, i, N = 0, 1, N * 2

        while i <= N ** 0.5:
            j = N / i
            ans += j == int(j) and j % 2 != i % 2
            i += 1

        return ans

    def doit_math(self, N):
        res = 1
        i = 3
        while N % 2 == 0:
            N /= 2
        while i * i <= N:
            count = 0
            while N % i == 0:
                N /= i
                count += 1
            res *= count + 1
            i += 2
        return res if N == 1 else res * 2

    # N = (x + 1) + ... + (x + k)
    # N = x k + k(k + 1)/2
    def doit_math_1(self, N: int) -> int:
        from math import ceil
        count = 0
        # x > 0 --> N/k - (k + 1)/2 > 0
        upper_limit = ceil((2 * N + 0.25) ** 0.5 - 0.5) + 1
        for k in range(1, upper_limit):
            # x should be integer
            if (N - k * (k + 1) // 2) % k == 0:
                count += 1
        return count
