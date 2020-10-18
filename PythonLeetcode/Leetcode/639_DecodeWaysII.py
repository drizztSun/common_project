"""
# 639. Decode Ways II

# A message containing letters from A-Z is being encoded to numbers using the following mapping way:

# 'A' -> 1
# 'B' -> 2
# ...
# 'Z' -> 26
# Beyond that, now the encoded string can also contain the character '*',
# which can be treated as one of the numbers from 1 to 9.

# Given the encoded message containing digits and the character '*', return the total number of ways to decode it.

# Also, since the answer may be very large, you should return the output mod 109 + 7.

# Example 1:
# Input: "*"
# Output: 9
# Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".

# Example 2:
# Input: "1*"
# Output: 9 + 9 = 18
"""


class DecodeWaysII:

    """
    # Let's keep track of:

    # e0 = current number of ways we could decode, ending on any number;
    # e1 = current number of ways we could decode, ending on an open 1;
    # e2 = current number of ways we could decode, ending on an open 2;
    # (Here, an �open 1� means a 1 that may later be used as the first digit of a 2 digit number,
    # because it has not been used in a previous 2 digit number.)

    # With the right idea of what to keep track of, our dp proceeds straightforwardly.

    # Say we see some character c. We want to calculate f0, f1, f2, the corresponding versions of e0, e1, e2 after parsing character c.

    # If c == '*', then the number of ways to finish in total is: we could put * as a single digit number (9*e0),
    # or we could pair * as a 2 digit number 1* in 9*e1 ways, or we could pair * as a 2 digit number 2* in 6*e2 ways.
    # The number of ways to finish with an open 1 (or 2) is just e0.

    # If c != '*', then the number of ways to finish in total is: we could put c as a single digit if it is not zero ((c>'0')*e0),
    # or we could pair c with our open 1, or we could pair c with our open 2 if it is 6 or less ((c<='6')*e2).
    # The number of ways to finish with an open 1 (or 2) is e0 iff c == '1' (or c == '2').
    """
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        mod = 10**9 + 7
        E0, E1, E2 = 1, 0, 0
        F1, F2, F3 = 0, 0, 0

        for c in s:
            
            if c == '*':
                F0 = 9*E0 + 9*E1 + 6*E2
                F1 = F2 = E0
            else:
                F0 = int( c > '0' ) * E0 + E1 + int(c < '7') * E2
                F1 = E0 if c == '1' else 0
                F2 = E0 if c == '2' else 0

            E0, E1, E2 = F0 % mod, F1, F2
    
        return E0

    """
    # The idea is DP. One of the hints is that you need mod the answer with a huge prime number.

    # For any string s longer than 2, we can decode either the last 2 characters as a whole or 
    # the last 1 character. So dp[i] = dp[i-1]* f(s.substr(i,1)) + dp[i-2]* f(s.substr(i-1, 2)). 
    # f() is the number of ways to decode a string of length 1 or 2.
    # f() could be 0, for example f(“67”).
    # There is a lot of cases and corner cases for f(string s). For example, * cannot be ‘0’, so ** has 15 instead of 16 possibilities, 
      because “20” is excluded. But the time complexity is still O(n).
    # The code is as below.
    """
    def doit_dp(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp = [0 for _ in range(len(s) + 1)]
        dp[0] = 1
        mod = 10 ** 9 + 7

        for i in range(1, len(s) + 1):

            if s[i - 1] != '0':
                dp[i] = (dp[i - 1] * (9 if s[i - 1] == '*' else 1)) % mod

            if i > 1:
                if s[i - 2] != '*' and s[i - 1] != '*':
                    if int(s[i - 2:i]) in range(10, 27):
                        dp[i] += dp[i - 2]

                elif s[i - 1] != '*' and s[i - 2] == '*':
                    dp[i] += (dp[i - 2] * (2 if int(s[i - 1]) <= 6 else 1)) % mod

                elif s[i - 1] == '*' and s[i - 2] != '*':
                    c2 = int(s[i - 2])
                    if c2 == 2:
                        dp[i] = (dp[i] + dp[i - 2] * 6) % mod
                    elif c2 == 1:
                        dp[i] = (dp[i] + dp[i - 2] * 9) % mod
                else:
                    dp[i] = (dp[i] + dp[i - 2] * 15) % mod

        return dp[-1]

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10 ** 9 + 7
        e0, e1, e2 = 1, 0, 0
        for c in s:
            if c == '*':
                f0 = 9 * e0 + 9 * e1 + 6 * e2
                f1 = e0
                f2 = e0
            else:
                f0 = (c > '0') * e0 + e1 + (c < '7') * e2
                f1 = (c == '1') * e0
                f2 = (c == '2') * e0

            e0 = f0 % MOD
            e1 = f1
            e2 = f2
        return e0

    def doit_dfs(self, s):
        """
        :type s: str
        :rtype: int
        """
        def helper(u):
    
            if len(u) == 1:
                return 9 if u == '*' else ( 0 if u == '0' else 1)
            else :
                if u == '**': # 10~26 but '*' is not 0 
                    return 15;
                elif u[0] == '*':
                    return 2 if u[1] <= '6' else 1
                elif u[1] == '*':
                    return 0 if u[0] not in ('1', '2') else (6 if u[0] == '2' else 9)
                else:
                    return 1 if 10 <= int(u) <= 26 else 0
                                 
        
        f1, f2 = 1, helper(s[0])
        mod = 10**9 + 7
        for i in range(1, len(s)):

            f3 = f1 * helper(s[i-1:i+1]) + f2 * helper(s[i:i+1])
            f1 = f2
            f2 = f3 % mod

        return f2


if __name__ == "__main__":

    res = DecodeWaysII().doit("*")

    res = DecodeWaysII().doit("1*")

    res = DecodeWaysII().doit("**")

    res = DecodeWaysII().doit("*1*1*0")

    res = DecodeWaysII().doit("***")

    res = DecodeWaysII().doit("****")

    res = DecodeWaysII().doit("*********")