"""
1278. Palindrome Partitioning III

You are given a string s containing lowercase letters and an integer k. You need to :

First, change some characters of s to other lowercase English letters.
Then divide s into k non-empty disjoint substrings such that each substring is palindrome.
Return the minimal number of characters that you need to change to divide the string.



Example 1:

Input: s = "abc", k = 2
Output: 1
Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
Example 2:

Input: s = "aabbc", k = 3
Output: 0
Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
Example 3:

Input: s = "leetcode", k = 8
Output: 0


Constraints:

1 <= k <= s.length <= 100.
s only contains lowercase English letters.

"""


class PalindromePartitionIII:

    def doit_dp(self, s: str, k: int) -> int:

        N = len(s)
        min_change = [[N+1 for _ in range(N)] for _ in range(N)]

        for L in range(N):
            for i in range(N - L):
                j = i + L
                if i == j:
                    min_change[i][j] = 0
                else:
                    min_change[i][j] = min_change[i + 1][j - 1] if i + 1 != j else 0
                    if s[i] != s[j]:
                        min_change[i][j] += 1

        dp = [[float('inf') for _ in range(N)] for _ in range(k)]
        dp[0] = min_change[0]

        for n in range(1, k):
            for j in range(n, N):
                for i in range(j, n-1, -1):
                    dp[n][j] = min(dp[n][j], min_change[i][j] + dp[n-1][i-1])

        return dp[k-1][N-1]


if __name__ == '__main__':

    PalindromePartitionIII().doit_dp( s = "abc", k = 2)

    PalindromePartitionIII().doit_dp( s = "aabbc", k = 3)

    PalindromePartitionIII().doit_dp( s = "leetcode", k = 8)