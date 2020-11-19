"""
712. Minimum ASCII Delete Sum for Two Strings

Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
Note:

0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].

"""


class MinimumDeleteSum:

    def doit_dp(self, s1: str, s2: str) -> int:

        m, n = len(s1), len(s2)
        dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

        for i in range(m + 1):

            for j in range(n + 1):

                if i == 0 and j == 0:
                    dp[i][j] = 0
                elif i == 0:
                    dp[i][j] = dp[i][j - 1] + ord(s2[j - 1])
                elif j == 0:
                    dp[i][j] = dp[i - 1][j] + ord(s1[i - 1])
                else:

                    if s1[i - 1] == s2[j - 1]:
                        dp[i][j] = dp[i - 1][j - 1]
                    else:
                        dp[i][j] = min(dp[i - 1][j] + ord(s1[i - 1]), dp[i][j - 1] + ord(s2[j - 1]))

        return dp[m][n]

    def doit_dp(self, s1: str, s2: str) -> int:

        string_sums = [0, 0]
        s2_sequences = [0] * (len(s2) + 1)

        for i in range(len(s1)):
            string_sums[0] += ord(s1[i])

        for i in range(len(s2)):
            string_sums[1] += ord(s2[i])

        for i in range(len(s1)):
            best_sequence_data = s2_sequences[-1]

            for j in range(len(s2)):
                temp = best_sequence_data

                if (s2_sequences[j] > best_sequence_data):
                    temp = s2_sequences[j]

                if (s2[j] == s1[i]):
                    s2_sequences[j] = best_sequence_data + ord(s1[i])

                best_sequence_data = temp

        highest_sum = 0

        for i in range(len(s2)):
            if (s2_sequences[i] > highest_sum):
                highest_sum = s2_sequences[i]

        return string_sums[0] + string_sums[1] - 2 * highest_sum
