""""
131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

Example:

Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]

"""

from collections import defaultdict


class PalindromePartitioning:

    def doit_dfs_topdown_dp(self, s):

        def search(i, memo):

            if len(s) == i:
                return [[]]

            if i in memo:
                return memo[i]

            res = []
            for j in range(i, len(s)):

                if s[i: j + 1] == s[i:j + 1][::-1]:
                    for c in search(j + 1, memo):
                        res.append([s[i: j + 1]] + c)

            memo[i] = res
            return res

        return search(0, {})

    def doit2(self, s: str):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        dp = [[False for _ in range(len(s))] for _ in range(len(s))]
        ans, current = [], []

        def dfs(i):
            nonlocal ans, current
            if i == len(s):
                ans.append(current[:])
                return
            
            dp[i][i] = True
            for j in range(i, len(s)):
                if s[i] == s[j] and (j - i <= 2 or dp[i+1][j-1]):
                    dp[i][j] = True
                    current.append(s[i:j+1])
                    dfs(j+1)
                    current.pop()
        dfs(0)
        return ans


if __name__ == '__main__':

    PalindromePartitioning.doit("aab")

