"""
1638. Count Substrings That Differ by One Character

Given two strings s and t, find the number of ways you can choose a non-empty substring of s and replace
a single character by a different character such that the resulting substring is a substring of t.
In other words, find the number of substrings in s that differ from some substring in t by exactly one character.

For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.

Return the number of substrings that satisfy the condition above.

A substring is a contiguous sequence of characters within a string.



Example 1:

Input: s = "aba", t = "baba"
Output: 6
Explanation: The following are the pairs of substrings from s and t that differ by exactly 1 character:
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
The underlined portions are the substrings that are chosen from s and t.
​​Example 2:
Input: s = "ab", t = "bb"
Output: 3
Explanation: The following are the pairs of substrings from s and t that differ by 1 character:
("ab", "bb")
("ab", "bb")
("ab", "bb")
​​​​The underlined portions are the substrings that are chosen from s and t.
Example 3:
Input: s = "a", t = "a"
Output: 0
Example 4:

Input: s = "abe", t = "bbc"
Output: 10


Constraints:

1 <= s.length, t.length <= 100
s and t consist of lowercase English letters only.

"""


class CountSubstringsDifferByOneCharacter:

    """
     1638.Count-Substrings-That-Differ-by-One-Character
     最初的感觉可能是一道双序列型的DP。所以我首先写出的是状态变量dp[i][j]，表示字符串s的前i个、字符串t的前j个能有多少种答案。接下来我就会考虑如何从s[i]和t[j]下手：怎么样能使得s[i]和t[j]是符合要求的substring的一部分？

     我发现，当s[i]!=t[j]的时候，我们不得不计算s[i]和t[j]之前有多少个连续的、相等的字符的个数a。这个时候灵光一现，如果我们也计算出s[i]和t[j]之后有多少个连续的、相等的字符的个数b，那么我们其实就解决了一类符合题意的substring的pattern：
     那就是以s[i]和t[j]做为“Differ by One Character”的位置，那么这样的字符串其实就是有(a+1)*(b+1)个。事实上，所有的符合条件的substring都可以归为若干类，每一类都有着相同的“Differ by One Character”的位置(i,j).

     所以至此，本题的思路就有了。我们遍历所有的配对(i,j)，如何s[i]!=t[j]，那么我们就计算相应的a和b（定义见前），然后ret+=(a+1)*(b+1).至于a和b，显然我们提前计算出来。
     令dp1[i][j]表示s[i]和t[j]之前的最长的相同substring（包括s[i]和t[j]本身）；令dp2[i][j]表示s[i]和t[j]之后的最长的相同substring（包括s[i]和t[j]本身）。这两个量都很容易用动态规划来解决。

    """

    def doit_dp(self, s: str, t: str) -> int:

        m, n = len(s), len(t)
        left = [[0 for _ in range(n + 2)] for _ in range(m + 2)]
        right = [[0 for _ in range(n + 2)] for _ in range(m + 2)]

        s = '#' + s + '#'
        t = '#' + t + '#'

        for i in range(1, m + 1):
            for j in range(1, n + 1):

                if s[i] == t[j]:
                    left[i][j] = left[i - 1][j - 1] + 1
                else:
                    left[i][j] = 0

        for i in range(m, 0, -1):
            for j in range(n, 0, -1):

                if s[i] == t[j]:
                    right[i][j] = right[i + 1][j + 1] + 1
                else:
                    right[i][j] = 0

        ans = 0
        for i in range(1, m + 1):
            for j in range(1, n + 1):

                if s[i] != t[j]:
                    ans += (left[i - 1][j - 1] + 1) * (right[i + 1][j + 1] + 1)

        return ans


if __name__ == '__main__':

    CountSubstringsDifferByOneCharacter().doit_dp("abe", "bbc")
