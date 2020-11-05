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

    def doit_dfs(self):

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

    def doit1(self, s):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        self.n, record = len(s), defaultdict(list)

        def find_palindrome(i, j):
            while i >= 0 and j < self.n:
                if s[i] == s[j]:
                    record[i].append(j)
                else:
                    break
                i -= 1
                j += 1

        for i in range(self.n):
            find_palindrome(i, i)
            find_palindrome(i, i + 1)

        ans_dict = {}

        def dp(start):
            if start >= self.n:
                return [[]]

            ret = []
            for end in record[start]:
                next_start = end + 1
                if next_start in ans_dict:
                    tail = ans_dict[next_start]
                else:
                    tail = dp(next_start)

                for tmp in tail:
                    ret.append([s[start:next_start]] + tmp)
            ans_dict[start] = ret
            return ret

        return dp(0)

    def doit2(self, s: str):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        dp = [[False for _ in range(len(s))] for _ in range(len(s))]
        for i in range(len(s)):
            dp[i][i] = True




if __name__ == '__main__':

    PalindromePartitioning.doit("aab")

