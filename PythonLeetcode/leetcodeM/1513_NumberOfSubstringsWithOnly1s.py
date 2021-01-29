"""
1513. Number of Substrings With Only 1s


Given a binary string s (a string consisting only of '0' and '1's).

Return the number of substrings with all characters 1's.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.
Example 2:

Input: s = "101"
Output: 2
Explanation: Substring "1" is shown 2 times in s.
Example 3:

Input: s = "111111"
Output: 21
Explanation: Each substring contains only 1's characters.
Example 4:

Input: s = "000"
Output: 0
 

Constraints:

s[i] == '0' or s[i] == '1'
1 <= s.length <= 10^5

"""


class NumberOfSubstringWithOnly1S:

    def doit_(self, s: str) -> int:
        
        from functools import lru_cache
        
        length, total, ans, mod = 0, 0, 0, (10**9 + 7)
        
        @lru_cache(None)
        def ways(n):
            if n == 0: return 0
            return n + ways(n-1)
        
        for i in range(len(s) + 1):
            
            if i == len(s) or s[i] == '0':
                total = (total + ways(length)) % mod
                length = 0
            else:
                length += 1
                
        return total

    def doit_math(self, s: str) -> int:
        a, b, r = 0, 0, 0
        
        while a >= 0:
            
            r = r + (b - a) * (b - a + 1) // 2
        
            a = s.find("1", b)
            b = s.find("0", a) 
        
            if b == -1:
                b = len(s)
        
        return r % 1000000007