"""
1639. Number of Ways to Form a Target String Given a Dictionary

You are given a list of strings of the same length words and a string target.

Your task is to form target using the given words under the following rules:

target should be formed from left to right.
To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
Repeat the process until you form the string target.
Notice that you can use multiple characters from the same string in words provided the conditions above are met.

Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.



Example 1:

Input: words = ["acca","bbbb","caca"], target = "aba"
Output: 6
Explanation: There are 6 ways to form target.
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
Example 2:

Input: words = ["abba","baab"], target = "bab"
Output: 4
Explanation: There are 4 ways to form target.
"bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
"bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
"bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
"bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")
Example 3:

Input: words = ["abcd"], target = "abcd"
Output: 1
Example 4:

Input: words = ["abab","baba","abba","baab"], target = "abba"
Output: 16


Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 1000
All strings in words have the same length.
1 <= target.length <= 1000
words[i] and target contain only lowercase English letters.

"""


class NumberOfWays:

    def doit(self, W, T) -> int:
        from collections import Counter
        from functools import lru_cache

        n, m = len(W[0]), len(T)
        counts = [Counter([w[i] for w in W]) for i in range(n)]

        @lru_cache(None)
        def help(i, j):
            if n - i < m - j:
                return 0

            if j == m:
                return 1

            # if i == n: return 0
            return (counts[i][T[j]] * help(i + 1, j + 1) + help(i + 1, j)) % (10 ** 9 + 7)

        return help(0, 0)

    def doit_dp(self, words: list, result: str) -> int:

        M, N = len(words[0]), len(result)
        wordCnt = [[0 for _ in range(27)] for _ in range(M)]
        hMod = 10**9 + 7

        for w in words:
            for i, l in enumerate(w):
                wordCnt[i][ord(l) - ord('a')] += 1

        dp = [[0 for _ in range(N+1)] for _ in range(M+1)]
        for i in range(M):
            dp[i][0] = 1

        for i in range(1, M+1):

            for j in range(1, N+1):

                dp[i][j] = max(dp[i][j-1], dp[i-1][j])

                if wordCnt[i-1][ord(result[j-1]) - ord('a')] > 0:
                    dp[i][j] = (dp[i][j] + wordCnt[i-1][ord(result[j-1]) - ord('a')] * dp[i-1][j-1]) % hMod

        return dp[M][N]