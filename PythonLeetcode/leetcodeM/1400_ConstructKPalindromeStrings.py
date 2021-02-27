"""
1400. Construct K Palindrome Strings


Given a string s and an integer k. You should construct k non-empty palindrome strings using all the characters in s.

Return True if you can use all the characters in s to construct k palindrome strings or False otherwise.



Example 1:

Input: s = "annabelle", k = 2
Output: true
Explanation: You can construct two palindromes using all characters in s.
Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
Example 2:

Input: s = "leetcode", k = 3
Output: false
Explanation: It is impossible to construct 3 palindromes using all the characters of s.
Example 3:

Input: s = "true", k = 4
Output: true
Explanation: The only possible solution is to put each character in a separate string.
Example 4:

Input: s = "yzyzyzyzyzyzyzy", k = 2
Output: true
Explanation: Simply you can put all z's in one string and all y's in the other string. Both strings will be palindrome.
Example 5:

Input: s = "cr", k = 7
Output: false
Explanation: We don't have enough characters in s to construct 7 palindromes.


Constraints:

1 <= s.length <= 10^5
All characters in s are lower-case English letters.
1 <= k <= 10^5

"""


class CanConstruct:

    def doit_hashtable(self, s: str, k: int) -> bool:

        from collections import Counter

        if len(s) <= k:
            return len(s) == k

        cnt = Counter(s)

        values = cnt.values()

        ones, twos = 0, 0

        for c in values:

            if c % 2 == 1:
                c -= 1
                ones += 1

            if c == 0: continue

            if c % 2 == 0:
                twos += c // 2

        if ones >= k:
            return ones == k

        k -= ones

        return 2 * twos >= k

    def doit_(self, s, k):
        import collections
        return sum(i & 1 for i in collections.Counter(s).values()) <= k <= len(s)