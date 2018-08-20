


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
# One possible longest palindromic subsequence is "bb".

# <dp> <important> <str>
class longestPalindromeSubseq:


    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        d = {}

        def search(content):
            if s not in d:
                maxLen = 0
                for c in set(content):
                    start, end = content.find(c), content.rfind(c)
                    if end - start >= maxLen:
                         maxLen = max(maxLen, 1 if start == end else 2 + search(content[start+1 : end])

                d[s] = maxLen

            return d[s]

        return search(content)

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [ [1] * n for _ in range(n)]

        for step in range(1, len(s)):
            for i in range(len(s) - step):
                j = i + step
                if s[i] == s[j]:
                    dp[i][j] = 2 + (dp[i+1][j-1] if j-1 >= i+1 else 0)
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])

        return dp[0][-1]

    
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp = [1] * len(s)

        for j in range(1, len(s)):
            pre = dp[j]  # dp[j, j]
            # Getting dp[i,...j], right now in dp is dp[i..j-1]
            # start from j-1 not 0 in dp[0....j-1], so we get each dp[i, j] but last time result
            for i in reversed(range(0, j)):
                tmp = dp[i] # dp[i, j-1]
                if s[i] == s[j]:
                    # dp[i...j] should be dp[i+1,j-1] + 2, if s[i] == s[j]
                    dp[i] = 2 + pre if i+1 <= j -1 else 2
                else:
                    # if s[i] != s[j]
                    # it means that should be the maximum between dp[i+1, j] and dp[j, j-1]
                    # so here now, dp[i+1] is dp[i+1, j]
                    # so before assignment, dp[i] is dp[i, j-1] 
                    dp[i] = max(dp[i+1], dp[i])

                # Here, we keep old dp[i], it is dp[i,j-1], it is for dp[i+1, j]
                pre = tmp

        return dp[0] # finally, dp[0] is dp[0, len(s) -1]
        

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
                    
                    
        



if __name__=="__main__":

    res = longestPalindromeSubseq().doit("bbbab")

    res = longestPalindromeSubseq().doit("cbbd")

    res = longestPalindromeSubseq().doit("aaa")

    pass