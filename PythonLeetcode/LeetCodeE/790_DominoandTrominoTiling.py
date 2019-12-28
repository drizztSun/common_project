# 790. Domino and Tromino Tiling

# We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.

# XX  <- domino

# XX  <- "L" tromino
# X
# Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.

# (In a tiling, every square must be covered by a tile.
# Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)

# Example:
# Input: 3
# Output: 5
# Explanation:
# The five different ways are listed below, different letters indicates different tiles:
# XYZ XXZ XYY XXY XYY
# XYZ YYZ XZZ XYY XXY
# Note:

# N  will be in range [1, 1000].


class NumTilings:

    # Two dimension DP[i, j] array.
    # i is the i-th column of the grid.
    # j indicates 3 states of the i-th column.
    # 0 : Fully covered by a tile(Domino or Tromino).
    # 1 : Only top part is coverd by a tile.
    # 2 : Only bottom part is covered by a tile.
    # Now we can come up with 3 DP formulas:
    # dp[i,0] = dp[i-2,0] + dp[i-1,0] + dp[i-1,1] + dp[i-1,2];
    # dp[i,1] = dp[i-2,0] + dp[i-1,2];
    # dp[i,2] = dp[i-2,0] + dp[i-1,1];
    def doit(self, N):
        mod = 10 ** 9 + 7
        dp = [[0, 0, 0] for _ in range(N+1)]
        dp[0][0] = 1
        dp[1][0] = 1

        for i in range(2, N+1):
            dp[i][0] = (dp[i-1][0] + dp[i-1][1] +
                        dp[i-1][2] + dp[i-2][0]) % mod
            dp[i][1] = (dp[i-1][2] + dp[i-2][0]) % mod
            dp[i][2] = (dp[i-1][1] + dp[i-2][0]) % mod

        return dp[N][0]

    # Step 2:
    # Look at the formula again, DP[i, 1] and DP[i, 2] are equivalent.
    # So the formula can be simplified:

    # dp[i,0] = dp[i-2,0] + dp[i-1,0] + 2 * dp[i-1,1];
    # dp[i,1] = dp[i-2,0] + dp[i-1,1];
    # Do some math, get rid of dp[i-1,1] and dp[i,1] by :

    # dp[i-1,1] = 1/2 * (dp[i,0] - dp[i-2,0] - dp[i-1,0]);
    # dp[i,1] = 1/2 * (dp[i+1,0] - dp[i-1,0] - dp[i,0]);
    # Then we get :

    # 1/2 * (dp[i+1,0] - dp[i-1,0] - dp[i,0]) = dp[i-2,0] + 1/2 * (dp[i,0] - dp[i-2,0] - dp[i-1,0]);
    # dp[i+1,0] **- dp[i-1,0]** - dp[i,0] = 2 * dp[i-2,0] + dp[i,0] - dp[i-2,0] **- dp[i-1,0]**;
    # dp[i+1,0] - dp[i,0] = 2 * **dp[i-2,0]** + dp[i,0] - **dp[i-2,0]**;
    # dp[i+1,0] - **dp[i,0]** = dp[i-2,0] + **dp[i,0]**;
    # dp[i+1,0] = dp[i-2,0] + 2 * dp[i,0];
    # dp[i,0] = dp[i-3,0] + 2 * dp[i-1,0];
    # Now, the formula can be converted to one dimension array.

    # dp[i] = dp[i-3] + 2 * dp[i-1];

    def doit(self, N):
        if N < 3:
            return N

        mod = 10 ** 9 + 7
        dp = [0] * (N+1)
        dp[0] = 1
        dp[1] = 1
        dp[2] = 2

        for i in range(3, N+1):
            dp[i] = (2 * dp[i-1] + dp[i-3]) % mod

        return dp[N]

    # Notice that in the formula we only need to track the last 3 previous result,
    # So we can replace the DP array by 3 variables:
    def doit(self, N):
        mod = 10 ** 9 + 7
        a, b, c, cur = 0, 1, 1, 1
        while N:
            cur = (2 * c + a) % mod
            a, b, c = b, c, cur
            N -= 1

        return cur

    def doit(self, N):
        if N < 3:
            return N

        a, b, c = 1, 1, 2
        cur = 0
        mod = 10 ** 9 + 7

        for i in range(3, N+1):
            cur = (2 * c + a) % mod
            a, b, c = b, c, cur

        return cur

    def doit(self, N):

        if N == 1:
            return 1
        if N == 2:
            return 2
        ppp, pp, p = 1, 1, 2
        for i in range(3, N+1):
            ppp, pp, p = pp, p, p * 2 + ppp

        return p % (10 ** 9 + 7)


if __name__ == '__main__':

    res = NumTilings().doit1(3)  # 5
