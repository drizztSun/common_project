import os


# leetcode 5.Longest Palindromic Substring

# Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

# Example:
# Input: "babad"
# Output: "bab"
# Note: "aba" is also a valid answer.


# Example:
# Input: "cbbd"
# Output: "bb"


class longestPalindrome:

    # 
    def doit1(self, s):
        """
        :type s: str
        :rtype: str
        """
        if not s:
            return ""

        i = 0
        longestOne = s[0]
        while i < len(s):
            start, end = i, i
            while 0 <= start <= end < len(s) and s[start] == s[end]:
                start -= 1
                end += 1

            if end - start - 1 > len(longestOne):
                longestOne = s[start + 1: end]

            start, end = i, i+1
            while 0 <= start <= end < len(s) and s[start] == s[end]:
                start -= 1
                end += 1

            if end - start - 1 > len(longestOne):
                longestOne = s[start + 1: end]

            i += 1

        return longestOne


    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        maxlen = 1
        start = 0
        if len(s) == 0:
            return 0
        
        for i in range(len(s)):
            if s[i-maxlen:i+1] == s[i-maxlen:i+1][::-1] and i-maxlen >= 0:
                start = i-maxlen
                maxlen += 1
                
            if s[i-maxlen-1:i+1] == s[i-maxlen-1:i+1][::-1] and i-maxlen-1 >= 0:
                start = i-maxlen-1
                maxlen += 2
               
        return s[start: start + maxlen]
            
            
        
# 516. Longest Palindromic Subsequence

# Given a string s, find the longest palindromic subsequence's length in s.
# You may assume that the maximum length of s is 1000.

# Example 1:        
# Input:
# "bbbab"
# Output:
# 4

# One possible longest palindromic subsequence is "bbbb".
# Example 2:
# Input:
# "cbbd"
# Output:
# 2

class longestPalindromeSubseq:

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        d = {}

        def search(s):
            if s not in d:
                maxlen = 0
                for c in set(s):
                    start, end = s.find(c), s.rfind(c)
                    maxlen = max(maxlen, 1 if start == end else 2 + search(s[start+1: end]))
                    
                d[s] = maxlen
                
            return d[s]
        
        return search(s)



# DP rule
# if s[i] == s[j]:
#   D[i, j] == D[i+1, j-1] + 2
# else:
#   D[i, j] = max(D[i+1, j], D[i, j-1])

    def doit2(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [[1] * 2 for _ in range(n)]

        for j in range(1, len(s)):
            for i in reversed(range(0, j)):
                if s[i] == s[j]:
                    dp[i][j%2] = 2 + dp[i + 1][(j - 1)%2] if i + 1 <= j - 1 else 2
                else:
                    dp[i][j%2] = max(dp[i + 1][j%2], dp[i][(j - 1)%2])

        return dp[0][(n-1)%2]


    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [1] * n

        for j in range(1, len(s)):
            pre = dp[j]
            for i in reversed(range(0, j)):
                tmp = dp[i]
                if s[i] == s[j]:
                    dp[i] = 2 + pre if i + 1 <= j - 1 else 2
                else:
                    dp[i] = max(dp[i + 1], dp[i])
                pre = tmp

        return dp[0]


    def doit3(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        D = [[1] * n for _ in range(n)]

        for step in range(1, n):
            for i in range(0, n-step):
                j = i + step
                if s[i] == s[j]:
                    if i + 1 <= j - 1:
                        D[i][j] = D[i+1][j-1] + 2
                    else:
                        D[i][j] = 2
                else:
           
                    D[i][j] = max(D[i+1][j], D[i][j-1])
            
        return D[0][n-1] 
        


if __name__=="__main__":


    res = longestPalindrome().doit("cbbd")


    res = longestPalindrome().doit("ccd")

    res = longestPalindromeSubseq().doit("bbbab")


    res = longestPalindromeSubseq().doit("cbbd")

    res = longestPalindromeSubseq().doit("aaa")

    pass
        