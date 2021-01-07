"""
935. Knight Dialer

# A chess knight can move as indicated in the chess diagram below:

# This time, we place our chess knight on any numbered key of a phone pad (indicated above), and the knight makes N-1 hops.
# Each hop must be from one key to another numbered key.

# Each time it lands on a key (including the initial placement of the knight), it presses the number of that key, pressing N digits total.

# How many distinct numbers can you dial in this manner?

# Since the answer may be large, output the answer modulo 10^9 + 7.


# Example 1:

# Input: 1
# Output: 10

# Example 2:

# Input: 2
# Output: 20

# Example 3:

# Input: 3
# Output: 46


# Note:

# 1 <= N <= 5000
"""


class KnightDialer:

    """
    Approach 1: Dynamic Programming
    Intuition

    Let f(start, n) be the number of ways to dial an n digit number, where the knight starts at square start.
    We can create a recursion, writing this in terms of f(x, n-1)'s.

    Algorithm

    By hand or otherwise, have a way to query what moves are available at each square.
    This implies the exact recursion for f. For example, from 1 we can move to 6, 8, so f(1, n) = f(6, n-1) + f(8, n-1).

    After, let's keep track of dp[start] = f(start, n), and update it for each n from 1, 2, ..., N.

    At the end, the answer is f(0, N) + f(1, N) + ... + f(9, N) = sum(dp).

    Complexity Analysis

    Time Complexity: O(N).

    Space Complexity: O(1).

    """

    def doit_dp(self, N):

        keys_hop = [[4, 6], [6, 8], [7, 9], [4, 8], [0, 3, 9], [], [0, 1, 7], [2, 6], [1, 3], [2, 4]]
        MOD = 10 ** 9 + 7
        dp = [1] * 10

        for _ in range(N-1):
            dp2 = [0] * 10
            for n, cnt in enumerate(dp):
                for c in keys_hop[n]:
                    dp2[c] += cnt
                    dp2[c] %= MOD
            dp = dp2
        return sum(dp) % MOD

    def doit_dp_1(self, N):

        keys = {0: [4, 6], 1: [6, 8], 2: [7, 9], 3: [4, 8], 4: [0, 3, 9], 5: [], 6: [0, 1, 7], 7: [2, 6], 8: [1, 3], 9: [2, 4]}
        MOD = 10 ** 9 + 7
        memo = {}

        def hop(i, times):

            if (i, times) in memo:
                return memo[(i, times)]

            if times == 1:
                return [str(i)]

            ans = []
            for c in keys[i]:
                for w in hop(c, times-1):
                    ans.append(str(i) + w)
            memo[(i, times)] = ans
            return ans

        ans = []
        for i in range(10):
            ans.extend(hop(i, N))

        return len(ans) % MOD


if __name__ == '__main__':

    res = KnightDialer().doit(1)  # 10

    res = KnightDialer().doit(2)  # 20

    res = KnightDialer().doit(3)  # 46
