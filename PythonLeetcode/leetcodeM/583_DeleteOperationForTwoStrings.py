"""
583. Delete Operation for Two Strings


Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

"""


class DeleteOperation:

    def doit_dp(self, word1: str, word2: str) -> int:

        m, n = len(word1), len(word2)
        dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

        for i in range(m + 1):

            for j in range(n + 1):

                if i == 0:
                    dp[i][j] = j
                elif j == 0:
                    dp[i][j] = i
                else:
                    #dp[i][j] = min(dp[i - 1][j - 1] + (2 if word1[i - 1] != word2[j - 1] else 0), min(dp[i - 1][j], dp[i][j - 1]) + 1)
                    if word1[i - 1] == word2[j - 1]:
                        dp[i][j] = dp[i - 1][j - 1]
                    else:
                        dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1

        return dp[m][n]

    def doit_dp_1(self, word1: str, word2: str) -> int:
        l1 = len(word1)
        l2 = len(word2)
        dp = [0]*(l2+1)

        for i in range(1, l1+1):
            prev = dp[0]
            for j in range(1, l2+1):
                last = dp[j]
                if word1[i-1] == word2[j-1]:
                    dp[j] = prev+1
                if prev < last:
                    prev = last
        maxlen = max(dp)
        res = l1-maxlen + l2-maxlen
        return res
