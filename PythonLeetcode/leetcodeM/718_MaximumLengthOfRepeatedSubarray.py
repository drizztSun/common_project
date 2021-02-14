"""
718. Maximum Length of Repeated Subarray


Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:

Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation:
The repeated subarray with maximum length is [3, 2, 1].


Note:

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100


"""


class MaximumLengthOfRepeatedSubarray:


    """
        718.Maximum-Length-of-Repeated-Subarray
        本题的本质就是Longest Common Subarray，和Longest Common Subsequence属于同一类的题目，双序列DP是最常规的解法。本题的状态转移方程更直观。

        根据双序列DP的套路，令dp[i][j]表示以i结尾的subarray和以j结尾的subarray相等的最大长度，则有：

        dp[i][j] = dp[i-1][j-1]+1 if A[i]==B[j] else 0
    """
    def doit_dp(self, A: list, B: list) -> int:

        m, n = len(A)+1, len(B)+1

        dp = [[0 for _ in range(m)] for _ in range(n)]

        res = 0

        for i in range(1, n):

            for j in range(1, m):

                dp[i][j] = (dp[i-1][j-1] + 1) if A[j-1] != B[i-1] else 0

                res = max(res, dp[i][j])

        return res