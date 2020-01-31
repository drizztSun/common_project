# 931. Minimum Falling Path Sum

# Given a square array of integers A, we want the minimum sum of a falling path through A.

# A falling path starts at any element in the first row, and chooses one element from each row.
# The next row's choice must be in a column that is different from the previous row's column by at most one.


# Example 1:

# Input: [[1,2,3],[4,5,6],[7,8,9]]
# Output: 12
# Explanation:
# The possible falling paths are:
# [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
# [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
# [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
# The falling path with the smallest sum is [1,4,7], so the answer is 12.


# Note:

# 1 <= A.length == A[0].length <= 100
# -100 <= A[i][j] <= 100


class MinFallingPathSum:

    def doit(self, A):

        path = [[float('inf') for _ in range(len(A))] for _ in range(len(A))]
        path[-1] = A[-1]

        for i in range(len(A)-2, -1, -1):
            for j in range(len(A)):
                for c in (j-1, j, j+1):
                    if c >= 0 and c < len(A):
                        path[i][j] = min(path[i][j], path[i+1][c] + A[i][j])

        return min(path[0])

    def doit(self, A):
        # A is square
        if len(A) == 1:
            return A[0][0]

        L = len(A)
        for i in range(1, len(A)):
            A[i][0] += min(A[i-1][0], A[i-1][1])
            A[i][-1] += min(A[i-1][-1], A[i-1][-2])
            for j in range(1, L-1):
                A[i][j] += min(A[i-1][j-1], A[i-1][j], A[i-1][j+1])

        return min(A[-1])

    def doit(self, A):
        MAX = 101
        n = len(A)

        dp = [[0 for _ in range(n)] for _ in range(n)]
        dp[0] = A[0].copy()

        for i in range(1, n):
            for j in range(n):
                dp[i][j] = min(dp[i - 1][k] if k >= 0 and k <
                               n else MAX for k in range(j - 1, j + 2)) + A[i][j]

        return min(dp[-1])

    """
    Approach 1: Dynamic Programming
    Intuition

    This problem has an optimal substructure, meaning that the solutions to subproblems can be used to solve larger instances of this problem. This makes dynamic programming an ideal candidate.

    Let dp(r, c) be the minimum total weight of a falling path starting at (r, c) and reaching the bottom row.

    Then, dp(r, c) = A[r][c] + min(dp(r+1, c-1), dp(r+1, c), dp(r+1, c+1)), and the answer is \min\limits_c \text{dp}(0, c)
    c
    min
    ​
    dp(0,c).

    Algorithm

    Usually, we would make an auxillary array dp to cache intermediate values dp(r, c). However, this time we will use A to cache these values. Our goal is to transform the values of A into the values of dp.

    We process each row, starting with the second last. (The last row is already correct.) We set A[r][c] = min(A[r+1][c-1], A[r+1][c], A[r+1][c+1]), handling boundary conditions gracefully.

    Let's look at the recursion a little more to get a handle on why it works. For an array like A = [[1,1,1],[5,3,1],[2,3,4]], imagine you are at (1, 0) (A[1][0] = 5). You can either go to (2, 0) and get a weight of 2, or (2, 1) and get a weight of 3. Since 2 is lower, we say that the minimum total weight at (1, 0) is dp(1, 0) = 5 + 2 (5 for the original A[r][c].)

    After visiting (1, 0), (1, 1), and (1, 2), A [which is storing the values of our dp], looks like [[1,1,1],[7,5,4],[2,3,4]]. We do this procedure again by visiting (0, 0), (0, 1), (0, 2). We get A = [[6,5,5],[7,5,4],[2,3,4]], and the final answer is min(A[0]) = 5

    Complexity Analysis

    Time Complexity: O(N^2), where NN is the length of A.

    Space Complexity: O(1) in additional space complexity.
    """

    def doit(self, A):

        while len(A) >= 2:
            row = A.pop()
            for i in range(len(row)):
                A[-1][i] += min(row[max(0, i-1): min(len(row), i+2)])
        return min(A[0])


if __name__ == '__main__':

    res = MinFallingPathSum().doit([[1, 2, 3], [4, 5, 6], [7, 8, 9]])  # 12

    pass
