"""
790. Domino and Tromino Tiling

We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.

XX  <- domino

XX  <- "L" tromino
X
Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.

(In a tiling, every square must be covered by a tile. Two tilings are different if and only if
there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)

Example:
Input: 3
Output: 5
Explanation:
The five different ways are listed below, different letters indicates different tiles:
XYZ XXZ XYY XXY XYY
XYZ YYZ XZZ XYY XXY
Note:

N  will be in range [1, 1000].


"""


class DominoAndTrominoTiling:

    """

    dp[i][0]: ways to cover i cols, both rows of col i are covered
    dp[i][1]: ways tp cover i cols, top row of col i is covered
    dp[i][2]: ways to cover i cols, bottom row of col i is covered

    init dp[0][0] = dp[1][0] = 1

    dp[i][0] = dp[i-1][0] + dp[i-2][0] + dp[i-1][1] + dp[i-1][2]
    dp[i][1] = dp[i-2][0] + dp[i-1][2]
    dp[i][2] = dp[i-2][0] + dp[i-1][1]


    dp[i][1] is always equals to dp[i][2], we can simplify

    dp[i][0] = dp[i-1][0] + dp[i-2][0] + 2 * dp[i-1][1]
    dp[i][1] = dp[i-2][0] + dp[i-1][1]

    """
    def doit_dp(self, n):

        if n < 3:
            return n

        mod = 10 ** 9 + 7
        dp = [[0 for _ in range(3)] for _ in range(n+1)]
        dp[0][0] = dp[1][0] = 1

        for i in range(2, n+1):
            dp[i][0] = (dp[i-1][0] + dp[i-2][0] + dp[i-1][1] + dp[i-1][2]) % mod
            dp[i][1] = (dp[i-2][0] + dp[i-1][2]) % mod
            dp[i][2] = (dp[i-2][0] + dp[i-1][1]) % mod

        return dp[-1][0]

    """
    Another way to think about this problem

    define: dp[i] ways to completely covert the i*2 board.
    dp[0] = 1 # {}
    dp[1] = 1 # {|}
    dp[2] = 2 # {||, =}
    dp[3] = 5 # {|||, |=, =|, ⌊⌉, ⌈⌋} = dp[2] ⊗ {|} + dp[1] ⊗ {=} + dp[0] ⊗ {⌊⌉, ⌈⌋}
    dp[4] = 11 # dp[3] ⊗ {|} + dp[2] ⊗ {=} + dp[1] ⊗ {⌊⌉, ⌈⌋} + dp[0] ⊗ {⌊¯⌋,⌈_⌉}
    dp[5] = 24 # dp[4] ⊗ {|} + dp[3] ⊗ {=} + 2*(dp[2] + dp[1] + dp[0])
    ...
    dp[n] = dp[n-1] + dp[n-2] + 2*(dp[n-3] + ... + dp[0])
          = dp[n-1] + dp[n-3] + [dp[n-2] + dp[n-3] + 2*(dp[n-4] + ... + dp[0])]
          = dp[n-1] + dp[n-3] + dp[n-1]
          = 2*dp[n-1] + dp[n-3]
    """
    def doit_dp(self, N: int) -> int:

        if N < 3:
            return N
        # a : [i-3][0]
        # b : [i-2][0]
        # c : [i-1][0]
        # cur : [i][0]
        a, b, c = 1, 1, 2
        cur = 0
        mod = 10 ** 9 + 7

        for i in range(3, N + 1):
            cur = (2 * c + a) % mod
            a, b, c = b, c, cur
        return cur

    """
    Approach #1: Dynamic Programming [Accepted]
    Intuition

    Let dp[state] be the previous number of ways to fill i columns where the i-th row of the last column is filled if the i-th bit of state is 1.

    In particular,
    dp[0] will be the number of ways to fill i columns where the last column has nothing filled;
    dp[1] will be the number of ways with the square in the last row filled;
    dp[2] will be the number of ways with the square in the first row filled; and
    dp[3] will be the number of ways with the squares in both rows filled.

    From there, we only have to accurately record the transitions.

    Algorithm

    If in the future we have:

    0 rows filled - it could have come from either:

    having 0 rows filled and a vertical domino, or
    both rows filled and nothing.
    last row filled - it could have come from either:

    having 0 rows filled and an L shaped tromino, or
    having top row filled and a horizontal domino
    first row filled - case is symmetric to the 'last row filled' case

    both rows filled - could have come from either:

    having 0 rows filled and two horizontal dominos, or
    having 1 row filled and an L shaped tromino (two cases.)
    After writing the recurrence correctly, the solution follows.

    Complexity Analysis

    Time Complexity: O(N). We update the state N times.
    Space Complexity: O(1).
    """
    def doit_dp(self, N):

        MOD = 10**9 + 7
        dp = [1, 0, 0, 0]
        for _ in range(N):
            ndp = [0, 0, 0, 0]
            ndp[0b00] = (dp[0b00] + dp[0b11]) % MOD
            ndp[0b01] = (dp[0b00] + dp[0b10]) % MOD
            ndp[0b10] = (dp[0b00] + dp[0b01]) % MOD
            ndp[0b11] = (dp[0b00] + dp[0b01] + dp[0b10]) % MOD
            dp = ndp

        return dp[0]


    """
    Approach #2: Matrix Exponentiation
    Intuition
    
    The recurrence expressed in Approach #1 expressed states that transitioned to a linear combination of other states. Any time this happens, we can represent the entire transition as a matrix of those linear combinations. Then, the nn-th power of this matrix represents the transition of nn moves, and thus we can reduce the problem to a problem of matrix exponentiation.
    
    Algorithm
    
    Let TT be the linear transformation taking dp -> ndp under the notation in Approach #1. Then, the matrix T^nT 
    n
      represents the transformation nn times in a row.
    
    To compute T^nT 
    n
      efficiently, we use the trick T^{2k} = T^k * T^kT 
    2k
     =T 
    k
     ∗T 
    k
      and T^{2k + 1} = T * T^{2k}T 
    2k+1
     =T∗T 
    2k
      to reduce the exponentiation to O(\log n)O(logn) multiplications. To multiply two matrices, we use the textbook definition.
    """

    def doit_dp_power(self, N):

        MOD = 10**9 + 7

        def matrix_mult(A, B):
            ZB = zip(*B)
            return [[sum(a * b for a, b in zip(row, col)) % MOD
                     for col in ZB] for row in A]

        def matrix_expo(A, K):
            if K == 0:
                return [[+(i==j) for j in range(len(A))]
                        for i in range(len(A))]
            if K == 1:
                return A
            elif K % 2:
                return matrix_mult(matrix_expo(A, K-1), A)

            B = matrix_expo(A, K/2)
            return matrix_mult(B, B)

        T = [[1, 0, 0, 1],
             [1, 0, 1, 0],
             [1, 1, 0, 0],
             [1, 1, 1, 0]]

        return matrix_expo(T, N)[0][0]


