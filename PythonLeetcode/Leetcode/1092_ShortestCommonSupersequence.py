"""
1092. Shortest Common Supersequence

Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.  If multiple answers exist, you may return any of them.

(A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)



Example 1:

Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation:
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.


Note:

1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.


"""


class ShortestCommonSupersequence:

    """
    Similar as Longest Commom Subsequence.
    After setting up DP table, we build shortest common supersequence, or scs, by backtracing.
    So when s1[i] == s2[j], we add that common char to scs. When dp[i-1][j] > dp[i][j-1], it indicates that there might be a char in s2[:j] that equals to s1[i].
    So we can add those "tail" in s2 to our scs until we reach such a j that s2[j] == s1[i].
    """
    def doit_dp(self, str1, str2):

        m, n = len(str1), len(str2)
        dp = [list(range(n + 1))] + [[i] + [0] * n for i in range(1, m + 1)]
        for i in range(m):
            for j in range(n):
                dp[i + 1][j + 1] = 1 + (dp[i][j] if str1[i] == str2[j] else min(dp[i + 1][j], dp[i][j + 1]))

        i, j, scs = m, n, ""
        while i > 0 and j > 0:
            if str1[i - 1] == str2[j - 1]:
                scs = str1[i - 1] + scs
                i, j = i - 1, j - 1
            elif dp[i - 1][j] > dp[i][j - 1]:
                scs = str2[j - 1] + scs
                j -= 1
            else:
                scs = str1[i - 1] + scs
                i -= 1
        return str1[:i] + str2[:j] + scs

    def doit_dp_2(self, str1, str2):
        m, n = len(str1), len(str2)
        dp = [list(range(n + 1))] + [[i] + [0] * n for i in range(1, m + 1)]
        for i in range(m):
            for j in range(n):
                dp[i + 1][j + 1] = 1 + (dp[i][j] if str1[i] == str2[j] else min(dp[i + 1][j], dp[i][j + 1]))

        i, j, scs = m, n, ""
        while i * j:
            f1, f2 = str1[i - 1] == str2[j - 1], dp[i - 1][j] < dp[i][j - 1]
            f1, f2 = int(f1 or f2), int(f1 or not f2)
            scs = str1[i - 1] * f1 + str2[j - 1] * (1 - f1) + scs
            i, j = i - f1, j - f2
        return str1[:i] + str2[:j] + scs

    def doit_dp_1(self, str1: str, str2: str) -> str:

        m, n = len(str1), len(str2)
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for i in range(m+1):
            for j in range(n+1):
                if i == 0:
                    dp[i][j] = j
                elif j == 0:
                    dp[i][j] = i
                else:
                    if str1[i-1] == str2[j-1]:
                        dp[i][j] = dp[i-1][j-1] + 1
                    else:
                        dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1

        i, j, scs = m, n, ''

        while i > 0 and j > 0:
            if str1[i-1] == str2[j-1]:
                scs = str1[i-1] + scs
                i -= 1
                j -= 1
            elif dp[i-1][j] > dp[i][j-1]:
                scs = str2[j-1] + scs
                j -= 1
            else:
                scs = str1[i-1] + scs
                i -= 1

        return str1[:i] + str2[:j] + scs

    def doit_dp_tle(self, str1: str, str2: str) -> str:

        N, M = len(str1), len(str2)
        dp = [['' for _ in range(M+1)] for _ in range(N+1)]

        for i in range(N+1):

            for j in range(M+1):

                if i == 0:
                    dp[i][j] = str2[:j]
                elif j == 0:
                    dp[i][j] = str1[:i]
                else:
                    if str1[i-1] == str2[j-1]:
                        dp[i][j] = dp[i-1][j-1] + str1[i-1]
                    else:
                        dp[i][j] = (dp[i-1][j] + str1[i-1]) if len(dp[i-1][j]) < len(dp[i][j-1]) else (dp[i][j-1] + str2[j-1])

        return dp[N][M]


if __name__ == '__main__':

    ShortestCommonSupersequence().doit_dp( str1 = "abac", str2 = "cab")