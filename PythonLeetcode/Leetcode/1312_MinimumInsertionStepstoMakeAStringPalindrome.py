"""
1312. Minimum Insertion Steps to Make a String Palindrome

Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.



Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.
Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".
Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
Example 4:

Input: s = "g"
Output: 0
Example 5:

Input: s = "no"
Output: 1


LCS: Longest Common Subsequence.
LPS: Longest Palindromic Subsequence.

"""


class MinInsertionsToPalindrome:

    def doit_dp(self, s: str) -> int:

        N = len(s)
        dp = [[N+1 for _ in range(N)] for _ in range(N)]

        for L in range(N):

            for i in range(N-L):

                j = i + L
                if i == j:
                    dp[i][j] = 0
                else:
                    if s[i] == s[j]:
                        dp[i][j] = dp[i+1][j-1] if i+1 != j else 0
                    else:
                        dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1

        return dp[0][N-1]

    def doit_dp_1(self, s: str) -> int:
        from functools import lru_cache

        @lru_cache(None)
        def dp(i, j):
            if i >= j:
                return 0

            return dp(i + 1, j - 1) if s[i] == s[j] else min(dp(i + 1, j) + 1, dp(i, j - 1) + 1)

        return dp(0, len(s) - 1)

    def doit_dp_2(self, s: str) -> int:
        prev = [0] * len(s)

        for i in range(len(s) - 1, -1, -1):
            curr = [0] * len(s)
            curr[i] = 1

            for j in range(i + 1, len(s)):
                if s[i] == s[j]:
                    curr[j] = prev[j - 1] + 2
                else:
                    curr[j] = max(curr[j - 1], prev[j])
            prev = curr
        return len(s) - prev[-1]


if __name__ == '__main__':

    MinInsertionsToPalindrome().doit_dp(s = "zzazz")

    MinInsertionsToPalindrome().doit_dp(s = "mbadm")

    MinInsertionsToPalindrome().doit_dp(s = "leetcode")

    MinInsertionsToPalindrome().doit_dp(s = "g")

    MinInsertionsToPalindrome().doit_dp(s = "no")

    MinInsertionsToPalindrome().doit_dp(s = "zjveiiwvc")