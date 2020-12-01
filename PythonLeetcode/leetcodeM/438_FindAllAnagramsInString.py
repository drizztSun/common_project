"""
438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

"""


class AllAnagramsString:

    def doit(self, s: str, p: str) -> list:
        from collections import Counter
        pset = Counter(p)
        l, cnt = len(p), Counter()
        i = 0
        ans = []

        while i < len(s):

            if s[i] in pset:
                cnt[s[i]] += 1

            if i >= l and s[i-l] in pset:
                cnt[s[i-l]] -= 1

            if pset == cnt:
                ans.append(i-l+1)

            i += 1

        return ans


if __name__ == '__main__':

    AllAnagramsString().doit("cbaebabacd", "abc")

    AllAnagramsString().doit("abab", "ab")