"""
1081. Smallest Subsequence of Distinct Characters


Return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.

"""


class SmallestSubsequence:
    
    def doit_(self, s: str) -> str:
        
        st = []
        last_pos = [-1] * 256
        for i, c in enumerate(s):
            last_pos[ord(s[i])] = i
        
        seen = set()
        for i, c in enumerate(s):
            
            if c not in seen:
                while st and st[-1] > c and last_pos[ord(st[-1])] > i:
                    seen.remove(st.pop())
                
                seen.add(c)
                st.append(c)
                
        return ''.join(st)
            