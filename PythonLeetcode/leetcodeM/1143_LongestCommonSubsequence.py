"""
1143. Longest Common Subsequence

Given two strings text1 and text2, return the length of their longest common subsequence.

A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order
of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings is a subsequence that is common to both strings.



If there is no common subsequence, return 0.



Example 1:

Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.


Constraints:

1 <= text1.length <= 1000
1 <= text2.length <= 1000
The input strings consist of lowercase English characters only.

"""


class LongestCommonSubsequence:


    """
    Similar as Longest Commom Subsequence.
    After setting up DP table, we build shortest common supersequence, or scs, by backtracing.
    So when s1[i] == s2[j], we add that common char to scs. When dp[i-1][j] > dp[i][j-1], it indicates that there might be a char in s2[:j] that equals to s1[i].
    So we can add those "tail" in s2 to our scs until we reach such a j that s2[j] == s1[i].

    """
    def doit_dp(self, text1: str, text2: str) -> int:

        n, m = len(text1), len(text2)

        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for i in range(1, m+1):
            for j in range(1, n+1):

                if text1[j-1] == text2[i-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        return dp[m][n]

    def doit_dp_with_sequence(self, text1: str, text2: str) -> int:

        n, m = len(text1), len(text2)

        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for i in range(1, m+1):
            for j in range(1, n+1):

                if text1[j-1] == text2[i-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        j, i, scs = n, m, ''

        while i > 0 and j > 0:

            if text2[i-1] == text1[j-1]:
                scs = text2[i-1] + scs
                j -= 1
                i -= 1
            elif dp[i-1][j] > dp[i][j-1]:
                i -= 1
            else:
                j -= 1

        return scs


if __name__ == '__main__':

    LongestCommonSubsequence().doit_dp_with_sequence(text1 = "abcde", text2 = "ace")