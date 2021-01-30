"""
1456. Maximum Number of Vowels in a Substring of Given Length

Given a string s and an integer k.

Return the maximum number of vowel letters in any substring of s with length k.

Vowel letters in English are (a, e, i, o, u).

 

Example 1:

Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
Example 2:

Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
Example 3:

Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.
Example 4:

Input: s = "rhythms", k = 4
Output: 0
Explanation: We can see that s doesn't have any vowel letters.
Example 5:

Input: s = "tryhard", k = 4
Output: 1
 

Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.
1 <= k <= s.length


"""


from typing import NamedTuple


class MaximumVowels:

    def doit_(self, s: str, k: int) -> int:

        ans, length = 0, 0
        vowel = set(['a', 'e', 'i', 'o', 'u'])
        
        for i in range(len(s)):
            
            length += 1 if s[i] in vowel else 0
            
            length -= 1 if i >= k and s[i-k] in vowel else 0
            
            ans = max(ans, length)
            
        return ans
                
        
