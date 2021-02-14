"""
1759. Count Number of Homogenous Substrings

Given a string s, return the number of homogenous substrings of s. Since the answer may be too large, return it modulo 109 + 7.

A string is homogenous if all the characters of the string are the same.

A substring is a contiguous sequence of characters within a string.



Example 1:

Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
Example 2:

Input: s = "xy"
Output: 2
Explanation: The homogenous substrings are "x" and "y".
Example 3:

Input: s = "zzzzz"
Output: 15


Constraints:

1 <= s.length <= 105
s consists of lowercase letters.



"""


class CountHomogenous:

    def doit_(self, s: str) -> int:

        last = None

        ans, hmod, count = 0, 10 ** 9 + 7, 0

        for i in range(len(s) + 1):

            if i == len(s) or s[i] != last:
                ans = (ans + count * (count + 1) // 2) % hmod
                count = 0

            if i != len(s):
                last = s[i]
                count += 1

        return ans

    """
        Explanation
        cur is the previous character in type integer,
        count the number of continuous same character.
        
        We iterate the whole string character by character,
        if it's same as the previous,
        we increment the count,
        otherwise we set it to 1.
        
        There are count characters to start with,
        ending at this current character,
        in order to construct a homogenous string.
        So increment our result res = (res + count) % mod.
        
        
        Complexity
        Time O(n)
        Space O(1)
        
        
        Solution 1
        
        Solution 2
    The number homogenous substring in a homogenous substring is
    n * (n + 1) / 2.
    Python
    """
    def doit_(self, s):
        from itertools import groupby
        res = 0
        for c, s in groupby(s):
            n = len(list(s))
            res += n * (n + 1) / 2
        return res % (10**9 + 7)

