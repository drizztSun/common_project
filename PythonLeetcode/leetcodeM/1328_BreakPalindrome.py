"""
1328. Break a Palindrome

Given a palindromic string palindrome, replace exactly one character by any lowercase English letter so that the string becomes the lexicographically smallest possible string that isn't a palindrome.

After doing so, return the final string.  If there is no way to do so, return the empty string.

 

Example 1:

Input: palindrome = "abccba"
Output: "aaccba"
Example 2:

Input: palindrome = "a"
Output: ""
 

Constraints:

1 <= palindrome.length <= 1000
palindrome consists of only lowercase English letters.

"""


class BreakPalindrome:

    def doit_(self, S: str) -> str:

        for i in range(len(S) // 2):
            if S[i] != 'a':
                return S[:i] + 'a' + S[i + 1:]

        return S[:-1] + 'b' if S[:-1] else ''

    """
        Check two candidates:

        Replace the first non-'a' with 'a'.
        Replace the last letter with 'b'.
            
    """
    def doit_(self, p):
        import re
        for s in re.sub('[^a]', 'a', p, 1), p[:-1] + 'b':
            if s < s[::-1]:
                return s
        return '' 