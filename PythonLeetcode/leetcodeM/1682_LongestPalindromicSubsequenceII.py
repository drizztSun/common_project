"""
1682. Longest Palindromic Subsequence II


A subsequence of a string s is considered a good palindromic subsequence if:

1. It is a subsequence of s.
2. It is a palindrome (has the same value if reversed).
3. It has an even length.
4. No two consecutive characters are equal, except the two middle ones.
For example, if s = "abcabcabb", then "abba" is considered a good palindromic subsequence, while "bcb" (not even length) and "bbbb" (has equal consecutive characters) are not.

Given a string s, return the length of the longest good palindromic subsequence in s.

 

Example 1:

Input: s = "bbabab"
Output: 4
Explanation: The longest good palindromic subsequence of s is "baab".
Example 2:

Input: s = "dcbccacdb"
Output: 4
Explanation: The longest good palindromic subsequence of s is "dccd".
 

Constraints:

1 <= s.length <= 250
s consists of lowercase English letters.


"""


class LongestPalindromeSubseq:

    def doit_dp(self, s: str) -> int:

        """
		dp[i][j] is a tuple of the length of the longest good palindrome substring between i and j (inclusive) and the ending char.
		if s[i]==s[j] and it is different from dp[i+1][j-1]'s ending char, then dp[i][j] = dp[i+1][j-1]+2;
		otherwise dp[i][j] is the max of dp[i+1][j], dp[i][j-1] and dp[i+1][j-1].
		"""
        n = len(s)
        dp = [[(0, '') for _ in range(n)] for _ in range(n)]

        for i in range(n-1, -1, -1):
            for j in range(i+1, n):

                if s[i] == s[j] and dp[i+1][j-1][1] != s[i]: #If it is end by s[i], then 
                    dp[i][j] = (dp[i+1][j-1][0] + 2, s[i])
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1], dp[i+1][j-1], key=lambda x: x[0])

        return dp[0][n-1][0]
    
    def doit_dp_1(self, s):
        n = len(s)
        dp = [[(0, '')] * n for _ in range(n)]

        for i in range(n - 1):
            if s[i] == s[i + 1]:
                dp[i][i + 1] = (2, s[i])

        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j] and dp[i + 1][j - 1][1] != s[i]:
                    dp[i][j] = (dp[i + 1][j - 1][0] + 2, s[i])
                else:
                    dp[i][j] = max((dp[i + 1][j], dp[i][j - 1], dp[i + 1][j - 1]), key = lambda x: x[0])

        return dp[0][-1][0]


    """
        Approach:

        Start with pointers i (at the start of s) and j (at the end of s) and prev_char ('@' a dummy character)
        Each step you have a few choices:

        1. If s[i] or s[j] equals prev_char then move that pointer inwards one step
        because the subesquence is not allowed to have two equal consecutive characters

        2. If s[i] equals s[j] then add 2 to the result, move both pointers inwards,
        and update prev_char

        3. If s[i] does not equal s[j] then consider moving i or moving j
        return the option that produces the best result

        As an exit condition, if i is ever greater than or equal to j then return zero
        because we cannot use the same character twice.
    """
    def longestPalindromeSubseq(self, s: str) -> int:
        from functools import lru_cache

        @lru_cache(None)
        def helper(i, j, prev_char):
            if i >= j:
                return 0
            if s[i] == s[j] and s[i] != prev_char:
                return 2 + helper(i+1, j-1, s[i])
                
            return max(helper(i+1, j, prev_char), helper(i, j-1, prev_char))

        res = helper(0, len(s) - 1, '@')
        # helper.cache_clear()
        return res