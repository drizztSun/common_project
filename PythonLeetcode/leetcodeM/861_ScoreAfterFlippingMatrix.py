# 861. Score After Flipping Matrix

# We have a two dimensional matrix A where each value is 0 or 1.

# A move consists of choosing any row or column, and toggling each value in that row or column:
# changing all 0s to 1s, and all 1s to 0s.

# After making any number of moves, every row of this matrix is interpreted as a binary number,
# and the score of the matrix is the sum of these numbers.

# Return the highest possible score.

# Example 1:

# Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
# Output: 39
# Explanation:
# Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
# 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39


# Note:

# 1 <= A.length <= 20
# 1 <= A[0].length <= 20
# A[i][j] is 0 or 1.

class MatrixScore:

    """
    Approach 1: Brute Force
    Intuition

    Notice that a 1 in the iith column from the right, contributes 2^i2
    i
    to the score.

    Say we are finished toggling the rows in some configuration. Then for each column, (to maximize the score), we'll toggle the column if it would increase the number of 1s.

    We can brute force over every possible way to toggle rows.

    Algorithm

    Say the matrix has R rows and C columns.

    For each state, the transition trans = state ^ (state-1) represents the rows that must be toggled to get into the state of toggled rows represented by (the bits of) state.

    We'll toggle them, and also maintain the correct column sums of the matrix on the side.

    Afterwards, we'll calculate the score. If for example the last column has a column sum of 3, then the score is max(3, R-3), where R-3 represents the score we get from toggling the last column.

    In general, the score is increased by max(col_sum, R - col_sum) * (1 << (C-1-c)), where the factor (1 << (C-1-c)) is the power of 2 that each 1 contributes.

    Note that this approach may not run in the time allotted.

    Complexity Analysis

    Time Complexity: O(2^R * R * C), where R, CR,C is the number of rows and columns in the matrix.

    Space Complexity: O(C) in additional space complexity.
    """

    def doit(self, A):
        R, C = len(A), len(A[0])
        colsums = [0] * C
        for r in range(R):
            for c in xrange(C):
                colsums[c] += A[r][c]

        ans = 0
        for r in range(1 << R):
            if r:
                trans = r ^ (r-1)
                for bit in range(R):
                    if (trans >> bit) & 1:
                        for c in range(C):
                            colsums[c] += -1 if A[bit][c] else +1
                            A[bit][c] ^= 1

            score = sum(max(x, R - x) * (1 << (C-1-c))
                        for c, x in enumerate(colsums))
            ans = max(ans, score)

        return ans

    """
    Approach 2: Greedy
    Intuition

    Notice that a 1 in the iith column from the right, contributes 2^i to the score.
    Since 2^n > 2^{n-1} + 2^{n-2} + ... + 2^0, maximizing the left-most digit is more important than any other digit.
    Thus, the rows should be toggled such that the left-most column is either all 0 or all 1 (so that after toggling the left-most column [if necessary],
    the left column is all 1.)

    Algorithm

    If we toggle rows by the first column (A[r][c] ^= A[r][0]), then the first column will be all 0.
    Afterwards, the base score is max(col, R - col) where col is the column sum; and (1 << (C-1-c)) is the power of 2 that each 1 in that column contributes to the score.

    Complexity Analysis

    Time Complexity: O(R * C), R, CR,C is the number of rows and columns in the matrix.
    Space Complexity: O(1) in additional space complexity.
    """

    def doit(self, A):
        R, C = len(A), len(A[0])
        ans = 0

        for c in range(C):
            col = 0
            for r in range(R):
                col += A[r][c] ^ A[r][0]
            ans += max(col, R - col) * 2 ** (C-c-1)
        return ans


if __name__ == '__main__':

    res = MatrixScore().doit([[0, 0, 1, 1], [1, 0, 1, 0], [1, 1, 0, 0]])  # 39

    pass