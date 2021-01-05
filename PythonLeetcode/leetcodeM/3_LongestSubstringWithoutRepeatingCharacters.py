"""
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.



Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
Example 4:

Input: s = ""
Output: 0


Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

"""


class LengthOfLongestSubstring:

    def doit(self, s: str) -> int:

        length = 0
        pos = {}
        ans = 0
        for i in range(len(s)):

            if s[i] in pos and length >= i - pos[s[i]]:
                length = i - pos[s[i]] - 1

            pos[s[i]] = i
            length += 1
            ans = max(ans, length)

        return ans


    """
    Approach 3: Sliding Window Optimized
    The above solution requires at most 2n steps. In fact, it could be optimized to require only n steps. 
    Instead of using a set to tell if a character exists or not, we could define a mapping of the characters to its index. Then we can skip the characters immediately when we found a repeated character.

    The reason is that if s[j]s[j] have a duplicate in the range [i, j)[i,j) with index j'j 
    ′
    , we don't need to increase ii little by little. We can skip all the elements in the range [i, j'][i,j 
    ′
    ] and let ii to be j' + 1j 
    ′
    +1 directly.

    Java (Using HashMap)

    """