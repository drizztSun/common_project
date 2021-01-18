"""
516. Longest Palindromic Subsequence

Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
 

Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".
 

Constraints:

1 <= s.length <= 1000
s consists only of lowercase English letters.

"""


class LongestPalindromeSubseq:

    def doit_dp_topdown(self, s: str) -> int:

        d = {}
        def search(s):
        
            if s in d:
                return d[s]

            maxLen = 0
            for c in set(s):
                start, end = s.find(c), s.rfind(c)
                if end - start >= maxLen:
                    maxLen = max(maxLen, 1 if start == end else 2 + search(s[start+1 : end]))

            d[s] = maxLen
            return maxLen
        
        return search(s)