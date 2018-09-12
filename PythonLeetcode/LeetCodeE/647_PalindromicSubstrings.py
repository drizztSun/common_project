# 647. Palindromic Substrings

# Given a string, your task is to count how many palindromic substrings in this string.

# The substrings with different start indexes or end indexes are counted as different substrings 
# even they consist of same characters.

# Example 1:
# Input: "abc"
# Output: 3
# Explanation: Three palindromic strings: "a", "b", "c".
# Example 2:
# Input: "aaa"
# Output: 6
# Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
# Note:
# The input string length won't exceed 1000.


class CountSubstrings:
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp = [ [False for _ in range(len(s))] for _ in range(len(s))]
        sum = len(s)
        for i in range(len(s)):
            dp[i][i] = True

        for i in range(len(s) - 1, -1, -1):
            for j in range(i+1, len(s)):
                 if s[i] == s[j]:
                    if j == i + 1 or dp[i+1][j-1]:
                        dp[i][j] = True
                        sum += 1

        return sum



if __name__ == "__main__":

    res = CountSubstrings().doit("abc")

    res = CountSubstrings().doit("aaa")
