"""
1216. Valid Palindrome III

Given a string s and an integer k, find out if the given string is a K-Palindrome or not.

A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.



Example 1:

Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.


Constraints:

1 <= s.length <= 1000
s has only lowercase English letters.
1 <= k <= s.length

"""

class IsValidPalindromeIII:

    def doit_dp(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        n = len(s)
        if n - k < 2:
            return True

        lps = [ [0]*n for _ in range(n) ]
        for i in range(n):
            lps[i][i] = 1
        for l in range(2, n + 1):
            # n = 5
            # l = 2
            # i = 0
            # j = 1
            for i in range(n - l + 1):
                j = i + l - 1
                if s[i] == s[j]:
                    lps[i][j] = max(lps[i+1][j-1]+2, lps[i+1][j], lps[i][j-1])
                else:
                    lps[i][j] = max(lps[i+1][j], lps[i][j-1])
        return lps[0][n-1] >= n - k

    def doit_dp_min_move(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        n = len(s)
        dp = [[float('inf') for _ in range(n)] for _ in range(n)]

        for step in range(0, n):

            for i in range(n-step):
                j = i + step
                if j - i < 2:
                    dp[i][j] = 0 if s[i] == s[j] else 1
                    continue

                dp[i][j] = dp[i+1][j-1] + (0 if s[i] == s[j] else 2)

                dp[i][j] = min(dp[i][j], min(dp[i+1][j], dp[i][j-1]) + 1)

        return dp[0][n-1] <= k


if __name__ == '__main__':

    IsValidPalindromeIII().doit_dp(s="bbbbabbb", k=2)

    IsValidPalindromeIII().doit_dp(s = "abcdeca", k = 2)

