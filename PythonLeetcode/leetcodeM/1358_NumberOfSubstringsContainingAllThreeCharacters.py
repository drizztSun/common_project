"""
1358. Number of Substrings Containing All Three Characters

Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.

"""


class NumberOfSubstrings:

    """
        Solution 1: Sliding Window
        Find many similar sliding window problem at the end of post.

        Time O(N)
        Space O(1)
    """
    def doit_slidingwindow(self, s: str) -> int:
        
        res = i = 0
        cnt = {c: 0 for c in 'abc'}

        for j in range(len(s)):

            cnt[s[j]] += 1

            while all(cnt.values()):
                cnt[s[i]]-=1
                i += 1

            res += i

        return res

    """
        Solution II
        last will record the position of last occurrence.
        If the ending index of substring is i,
        the starting position should be on the left of min(last),
        in order to have all 3 different letters.
        And in this case, the starting index can be in range [0, min(last)],
        min(last) + 1 in total.

        Time O(N)
        Space O(1)
    """
    def doit_slidingwindow_1(self, s):
        res, last = 0, [-1] * 3
        for i, c in enumerate(s):
            last[ord(c) - 97] = i
            res += 1 + min(last)
        return res