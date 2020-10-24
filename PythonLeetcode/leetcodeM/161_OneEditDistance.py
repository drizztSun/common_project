"""
161. One Edit Distance

Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:

Insert exactly one character into s to get t.
Delete exactly one character from s to get t.
Replace exactly one character of s with a different character to get t.


Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.
Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.
Example 3:

Input: s = "a", t = ""
Output: true
Example 4:

Input: s = "", t = "A"
Output: true


Constraints:

0 <= s.length <= 104
0 <= t.length <= 104
s and t consist of lower-case letters, upper-case letters and/or digits.
"""


class IsOneEditDistance:

    """
    Approach 1: One pass algorithm
    Intuition

    First of all, let's ensure that the string lengths are not too far from each other. If the length difference is 2 or more characters, then s and t couldn't be one edit away strings.

    For the next let's assume that s is always shorter or the same length as t. If not, one could always call isOneEditDistance(t, s) to inverse the string order.

    s = "abcdef"
    t = "abcd"

    Now it's time to pass along the strings and to look for the first different character.
    If there is no differences between the first len(s) characters, only two situations are possible :
    The strings are equal.
    The strings are one edit away distance.

    If the first len(s) characters are the same:
    s = "abcd"                      s = "abcd"
    t = "abcd"                      t = "abcde"
    1. The string are equal         2. The Strings are one edit distance

    Now what if there is a different character so that s[i] != t[i].

    1) If the strings are of the same length, all next characters should be equal to keep one edit away distance.
    To verify it, one has to compare the substrings of s and t both starting from the i + 1th character.

    2) If t is one character longer than s, the additional character t[i] should be the only difference between both strings.
    To verify it, one has to compare a substring of s starting from the ith character and a substring of t starting from the i + 1th character.




    Complexity Analysis

    Time complexity : O(N) in the worst case when string lengths are close enough abs(ns - nt) <= 1,
    where N is a number of characters in the longest string.
    O(1) in the best case when abs(ns - nt) > 1.

    Space complexity : O(N) because strings are immutable in Python and Java and to create substring costs O(N) space.
    """

    def isOneEditDistance(self, s, t):
        ns, nt = len(s), len(t)

        # Ensure that s is shorter than t.
        if ns > nt:
            return self.isOneEditDistance(t, s)

        # The strings are NOT one edit away distance
        # if the length diff is more than 1.
        if nt - ns > 1:
            return False

        for i in range(ns):
            if s[i] != t[i]:
                # if strings have the same length
                if ns == nt:
                    return s[i + 1:] == t[i + 1:]
                # if strings have different lengths
                else:
                    return s[i:] == t[i + 1:]

        # If there is no diffs on ns distance
        # the strings are one edit away only if
        # t has one more character.
        return ns + 1 == nt

    def doit_dp(self, s: str, t: str):

        n, m = len(s), len(t)
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]
        dp[0] = [i for i in range(n+1)]
        dp[0][0] = 0

        for i in range(1, m+1):
            dp[i][0] = i
            for j in range(1, n+1):
                dp[i][j] = min(dp[i-1][j-1] + (1 if t[i-1] != s[j-1] else 0), min(dp[i-1][j], dp[i][j-1]) + 1)
        return dp[m][n] == 1


if __name__ == '__main__':

    IsOneEditDistance().doit_dp(s="ab", t="acb")

    IsOneEditDistance().doit_dp(s="a", t="")