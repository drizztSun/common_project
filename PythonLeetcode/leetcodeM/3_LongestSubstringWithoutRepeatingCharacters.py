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