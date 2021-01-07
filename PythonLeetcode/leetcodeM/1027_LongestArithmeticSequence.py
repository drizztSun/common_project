"""
# 1027. Longest Arithmetic Sequence

# Given an array A of integers, return the length of the longest arithmetic subsequence in A.

# Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1,
# and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).


# Example 1:

# Input: [3,6,9,12]
# Output: 4
# Explanation:
# The whole array is an arithmetic sequence with steps of length = 3.

# Example 2:

# Input: [9,4,7,2,10]
# Output: 3
# Explanation:
# The longest arithmetic subsequence is [4,7,10].

# Example 3:

# Input: [20,1,15,3,10,5,8]
# Output: 4
# Explanation:
# The longest arithmetic subsequence is [20,15,10,5].

Constraints:

2 <= A.length <= 1000
0 <= A[i] <= 500
"""


class LongestArithSeqLength:

    def doit_dp(self, A):

        from collections import defaultdict
        # dp for each element i, sequence length is j, and how manch elements in the sequence, ended by ith element.
        dp = defaultdict(lambda: defaultdict(lambda: 1))
        ans = 0

        for i in range(len(A)):

            for j in range(i-1, -1, -1):

                k = A[i] - A[j]

                dp[i][k] = max(dp[i][k], dp[j][k]+1)

                ans = max(dp[i][k], ans)

        return ans

    def doit_dp_1(self, A):
        import collections
        if not A:
            return 0
        d = collections.defaultdict(lambda: collections.defaultdict(lambda: 1))
        res = 1
        for i in range(1, len(A)):
            for j in range(i - 1, -1, -1):
                k = A[i] - A[j]
                d[k][i] = max(d[k][i], d[k][j] + 1)
                res = max(res, d[k][i])
        return res

    # (DP)
    def doit_dp_2(self, A):

        n = len(A)
        indices = {}
        # dp[][] shows every two element,(i, j). How much A[i] and A[j] is in a sequence size, if they are in a sequence, by default it is two.
        dp = [[2] * n for _ in range(n)]
        res = 2

        for i in range(0, n):
            for j in range(i + 1, n):

                prev = indices.get(A[i] * 2 - A[j])
                if prev is not None and prev < i:

                    cur = max(dp[i][j], dp[prev][i] + 1)
                    res = max(res, cur)
                    dp[i][j] = cur

            indices[A[i]] = i

        return res


if __name__ == '__main__':

    res = LongestArithSeqLength().doit([3, 6, 9, 12])

    res = LongestArithSeqLength().doit([9, 4, 7, 2, 10])

    res = LongestArithSeqLength().doit([20, 1, 15, 3, 10, 5, 8])

    pass
