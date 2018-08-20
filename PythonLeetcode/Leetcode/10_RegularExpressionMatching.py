import os


# leetcode 10. Regular Expression Matching

# Implement regular expression matching with support for '.' and '*'.
# '.' Matches any single character.
# '*' Matches zero or more of the preceding element.

# The matching should cover the entire input string (not partial).

# The function prototype should be:
# bool isMatch(const char *s, const char *p)

# Some examples:
# isMatch("aa","a") ? false
# isMatch("aa","aa") ? true
# isMatch("aaa","aa") ? false
# isMatch("aa", "a*") ? true
# isMatch("aa", ".*") ? true
# isMatch("ab", ".*") ? true
# isMatch("aab", "c*a*b") ? true


class isMatch:
    def doit(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        def search(s, i, p, j, A):
            if j == len(p):
                return i == len(s)

            if (i, j) in A:
                return A[(i, j)]
        
            res = False
            isstar = j+1 < len(p) and p[j+1] == '*'

            if isstar:
                res = search(s, i, p, j+2, A) or i < len(s) and (s[i] == p[j] or p[j] == '.') and search(s, i+1, p, j, A )
            else:
                res = i < len(s) and (s[i] == p[j] or p[j] == '.') and search(s, i+1, p, j+1, A)

            A[(i,j)] = res

            return res
        
        return search(s, 0, p, 0, {})

    # <DP>
    def doit1(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        # *
        # * f[i][j]: if s[0..i-1] matches p[0..j-1]
        #
        # * if p[j - 1] != '*'
        # *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
        #
        # * if p[j - 1] == '*', denote p[j - 2] with x
        # *      f[i][j] is true iff any of the following is true
        # *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
        # *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
        # * '.' matches any single character
        # *
        m, n = len(s), len(p)
        D = [[False for _ in range(n+1)] for _ in range(m+1)]

        D[0][0] = True
        for i in range(1, n+1):
            D[0][i] = i > 1 and p[i-1] == '*' and D[0][i-2]
        
        for i in range(1, m+1):
            for j in range(1, n+1):

                if p[j-1] != '*':
                    D[i][j] = (s[i-1] == p[j-1] or p[j-1] == '.') and D[i-1][j-1]
                else:
                    D[i][j] = D[i][j-2] or ((s[i-1] == p[j-2] or p[j-2] == '.') and D[i-1][j])
                    # s[0..i-1] p[0..j] is matched, so '*' match one more time, 's[i-1]'
        return D[m][n]



    def doit3(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        matching = [[False] * (len(s) + 1) for _ in range(len(p) + 1)]
        
        matching[0][0] = True
        for i in range(len(p)):
            if p[i] == '*':
                matching[i+1][0] = matching[i-1][0]


        for i in range(len(p)):
            for j in range(len(s)):

                if p[i] == '*':
                    matching[i+1][j+1] = matching[i-1][j+1] or matching[i][j+1] or ((s[j] == p[i-1] or p[i-1] == '.') and matching[i+1][j])
                elif p[i] == '.' or s[j] == p[i]:
                    matching[i+1][j+1] = matching[i][j]

        return matching[-1][-1]

if __name__=="__main__":


    res = isMatch().doit("aa","a") # false

    res = isMatch().doit("aa","aa") # true

    res = isMatch().doit("aaa","aa") # false

    res = isMatch().doit("aa", "a*") # true

    res = isMatch().doit("aa", ".*") # true

    res = isMatch().doit("ab", ".*") # true

    res = isMatch().doit("aab", "c*a*b") # true

    res = isMatch().doit("aaa", "a*a") #true

    res = isMatch().doit("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c") 

    pass        

