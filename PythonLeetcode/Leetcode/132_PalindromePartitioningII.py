"""
132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.



Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1

IdP 1: https://eaadpqa-alpha-akamai-idp-dp.login.stage.akamai-access.com/
user: eaa-dp-qa@eaa-dp.com
pass: Wapp123$

IdP 2: https://delaware-idp.login.stage.akamai-access.com
user: svazhaka@akamai.com
pass: Wapp123$

"""


class MinCut(object):
    def doit_dp(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s) == 0:
            return 0

        # double DP, D is the minimum Partitioning
        D = [len(s) - x for x in range(len(s) + 1)]
        # dp for palindrome
        p = [[False for x in range(len(s))] for y in range(len(s))]

        # reverse string
        i = len(s) - 1
        while i >= 0:
            j = i
            while j < len(s):
                if s[i] == s[j] and (j - i < 2 or p[i + 1][j - 1]):
                    p[i][j] = True
                    D[i] = min(1 + D[j + 1], D[i])
                j += 1
            i -= 1

        return D[0] - 1

    def doit_dp_1(self, s):
        """
        :type s: str
        :rtype: int
        """
        if s == s[::-1]:
            return 0
        for i in range(1, len(s)):
            if s[:i] == s[:i][::-1] and s[i:] == s[i:][::-1]:
                return 1

        cut = [i for i in range(-1, len(s))]  # cut numbers in worst case (no palindrome)
        for i in range(len(s)):
            # odd palindrome
            l = r = i
            while l >= 0 and r < len(s) and s[l] == s[r]:
                cut[r+1] = min(cut[r+1], cut[l]+1)
                l -= 1
                r += 1
            # even palindrome
            l = i
            r = i + 1
            while l >= 0 and r < len(s) and s[l] == s[r]:
                cut[r+1] = min(cut[r+1], cut[l]+1)
                l -= 1
                r += 1
        return cut[-1]


if __name__ == '__main__':

    MinCut().doit_dp("aab")
