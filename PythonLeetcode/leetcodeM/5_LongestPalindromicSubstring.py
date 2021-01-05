"""
5. Longest Palindromic Substring

Given a string s, return the longest palindromic substring in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
Example 3:

Input: s = "a"
Output: "a"
Example 4:

Input: s = "ac"
Output: "a"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters (lower-case and/or upper-case),


"""


class longestPalindrome:

    """
    O(n)
    """
    def doit_(self, s: str) -> str:
        
        ### Method 5: A single pass:
        if s == s[::-1]: # add this line is helpful to reduce the runtime 
            return s

        max_len, i, left = 1, 0, 0
        while i < len(s) - (max_len//2):
            
            j = i-1 # find   xaaaaaaaax
            while i < len(s) -1 and s[i] == s[i+1]:
                i += 1

            i += 1
            k = i
            # search two directions
            while j >= 0 and k < len(s) and s[k] == s[j]:
                j, k = j-1, k+1
            if k - j - 1 > max_len:
                max_len, left = k - j - 1, j+1

        return s[left:left + max_len]

    def doit_search(self, s: str) -> str:
        pal_max = ""
        def longest_palindrome_helper(i, j, s):
            while i >= 0 and j < len(s) and s[i] == s[j]:
                i -= 1
                j += 1
            return s[i + 1:j]

        for k in range(len(s)):
            pal_odd = longest_palindrome_helper(k, k, s)
            pal_even = longest_palindrome_helper(k, k + 1, s)
            pal_max = max(pal_odd, pal_even, pal_max, key=len)
        return pal_max
    


    """
    O(n^2)
    """
    def doit_dp(self, s: str) -> str:

        n = len(s)
        dp = [[False for _ in range(n)] for _ in range(n)]
        res = ''
        
        for i in range(n):
            for j in range(i, -1, -1):        
                if s[i] == s[j] and (i - j < 2 or dp[j+1][i-1]):
                    dp[j][i] = True
                    if i - j + 1 > len(res):
                        res = s[j:i+1]
        return res