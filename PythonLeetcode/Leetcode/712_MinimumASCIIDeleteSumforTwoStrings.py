# 712. Minimum ASCII Delete Sum for Two Strings

# Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

# Example 1:
# Input: s1 = "sea", s2 = "eat"
# Output: 231
# Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
# Deleting "t" from "eat" adds 116 to the sum.
# At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

# Example 2:
# Input: s1 = "delete", s2 = "leet"
# Output: 403
# Explanation: Deleting "dee" from "delete" to turn the string into "let",
# adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
# At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
# If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

class MinimumDeleteSum:
    def doit(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        m, n = len(s1), len(s2)
        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

        for i in range(1, m + 1):
            dp[0][i] += dp[0][i-1] + ord(s1[i-1])

        for i in range(1, n + 1):
            dp[i][0] += dp[i-1][0] + ord(s2[i - 1])

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                    dp[i][j] = min(dp[i-1][j-1] + ord(s2[i-1]) + ord(s1[j-1]) if s2[i-1] != s1[j-1] else dp[i-1][j-1],
                                    dp[i-1][j] + ord(s2[i-1]),
                                    dp[i][j-1] + ord(s1[j-1]))                

        return dp[n][m]


class Solution:
    def minimumDeleteSum(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        l1=[]
        l2=[]
        ld=[]
        sum=0
        for c in s1:
            sum=sum+ord(c)
            if c in s2: l1.append(c)
            else: ld.append(c)
        
        for c in s2:
            sum=sum+ord(c)
            if c in l1: l2.append(c)
            else: ld.append(c)
        
        # print(ld)
        
        if len(l1)<len(l2):
            l3=l1
            l1=l2
            l2=l3
        
        n1=len(l1)
        n2=len(l2)
        if n1==0: return sum # anyway n2==0 too if n1==0        
        
        dp=[[0]*n2 for i in range(n1)]
        
        for i in range(l2.index(l1[0]),n2): dp[0][i]=ord(l1[0])
            
        # print(l1)
        # print(l2)
        
        for i in range(1,n1):
            dp[i][0]=dp[i-1][0]
            if l1[i]==l2[0] and ord(l1[i])>dp[i][0]: dp[i][0]=ord(l1[i])
            for j in range(1, n2):
                dp[i][j]=max(dp[i-1][j], dp[i][j-1])
                if l1[i]==l2[j]:
                    t=ord(l1[i])+dp[i-1][j-1]
                    if t>dp[i][j]: dp[i][j]=t
                    # else: print("WTF? l1[i]==l2[j] < max(dp[i-1][j],dp[i][j-1]) !!!")
        
        #print(dp)
        return sum-2*dp[n1-1][n2-1]

if __name__ == "__main__":

    res = MinimumDeleteSum().doit(s1 = "sea", s2 = "eat")

    res = MinimumDeleteSum().doit(s1 = "delete", s2 = "leet")

    res = 0
        