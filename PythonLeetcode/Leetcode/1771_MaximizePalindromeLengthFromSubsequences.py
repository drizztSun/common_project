"""
1771. Maximize Palindrome Length From Subsequences


You are given two strings, word1 and word2. You want to construct a string in the following manner:

Choose some non-empty subsequence subsequence1 from word1.
Choose some non-empty subsequence subsequence2 from word2.
Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.

A palindrome is a string that reads the same forward as well as backward.

 

Example 1:

Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
Example 2:

Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a palindrome.
Example 3:

Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so return 0.
 

Constraints:

1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.


"""


class LongestPalindrome:
    
    def doit_dp(self, word1: str, word2: str) -> int:
        
        word = word1 + word2
        n, n1 = len(word), len(word1)
        ret = 0
        dp = [[0 for _ in range(n)] for _ in range(n)]
        
        for i in range(n):
            dp[i][i] = 1
            
        for L in range(2, n + 1):
            for i in range(0, n - L + 1):
                j = i + L - 1
                
                if word[i] == word[j]:
                    
                    dp[i][j] = dp[i+1][j-1] + 2
                    
                    if i < n1 and j >= n1:
                        ret = max(ret, dp[i][j])
                    
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
                    
        return ret
        
        