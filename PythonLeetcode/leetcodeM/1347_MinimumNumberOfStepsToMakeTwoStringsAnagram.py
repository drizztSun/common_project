"""
1347. Minimum Number of Steps to Make Two Strings Anagram

Given two equal-size strings s and t. In one step you can choose any character of t and replace it with another character.

Return the minimum number of steps to make t an anagram of s.

An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.



Example 1:

Input: s = "bab", t = "aba"
Output: 1
Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.
Example 2:

Input: s = "leetcode", t = "practice"
Output: 5
Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.
Example 3:

Input: s = "anagram", t = "mangaar"
Output: 0
Explanation: "anagram" and "mangaar" are anagrams.
Example 4:

Input: s = "xxyyzz", t = "xxyyzz"
Output: 0
Example 5:

Input: s = "friend", t = "family"
Output: 4

"""
from collections import Counter


class MiinimumStepToAnagram:

    def doit(self,s ,t):

        return sum((Counter(s) - Counter(t)).values())

    def doit(self, s, t):

        ls = sorted(list(s))
        lt = sorted(list(t))

        res = len(s)
        ps, pt = 0, 0

        while ps < len(ls) and pt < len(lt):

            if ls[ps] == lt[pt]:
                ps += 1
                pt += 1
                res -= 1
            elif ord(ls[ps]) > ord(lt[pt]):
                pt += 1
            else:
                ps += 1

        return res

    def doit(self, s: str, t: str) -> int:

        from collections import Counter

        cntS, cntT = Counter(s), Counter(t)
        res = len(s)
        for c in cntS:
            if c in cntT:
                res -= min(cntT[c], cntS[c])
        return res
