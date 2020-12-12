"""
1208. Get Equal Substrings Within Budget

You are given two strings s and t of the same length. You want to change s to t. Changing the i-th character of s to i-th character
of t costs |s[i] - t[i]| that is, the absolute difference between the ASCII values of the characters.

You are also given an integer maxCost.

Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring of
twith a cost less than or equal to maxCost.

If there is no substring from s that can be changed to its corresponding substring from t, return 0.



Example 1:

Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd". That costs 3, so the maximum length is 3.
Example 2:

Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to charactor in t, so the maximum length is 1.
Example 3:

Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You can't make any change, so the maximum length is 1.


Constraints:

1 <= s.length, t.length <= 10^5
0 <= maxCost <= 10^6
s and t only contain lower case English letters.


"""


class EqualSubstring:

    def doit_search(self, s: str, t: str, maxCost: int) -> int:

        cost = [abs(ord(c1) - ord(c2)) for c1, c2 in zip(s, t)]

        j, total = 0, 0
        for i, c in enumerate(cost):

            total += cost[i]

            while j <= i and total > maxCost:
                total -= cost[j]
                j += 1

            ans = max(ans, i - j + 1)

        return ans

    def doit_search_1(self, s: str, t: str, maxCost: int) -> int:
        low = -1
        costs = [abs(ord(s[x]) - ord(t[x])) for x in range(len(s))]
        for high in range(len(s)):
            maxCost -= costs[high]
            if maxCost < 0:
                low += 1
                maxCost += costs[low]
        return high - low






