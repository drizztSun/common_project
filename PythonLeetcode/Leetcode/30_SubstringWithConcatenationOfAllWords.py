"""
# 30. Substring with Concatenation of All Words

You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that
is a concatenation of each word in words exactly once, in any order, and without any intervening characters.

You can return the answer in any order.



Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]

"""
import collections


class findSubstring(object):

    def doit(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []

        from collections import Counter
        gCnt = collections.Counter(words)
        nums, wl = len(words), len(words[0])
        res = []

        if len(s) < wl * nums:
            return []

        for i in range(wl):

            lCnt = Counter()
            left, c = i, 0
            for j in range(i, len(s) - wl + 1, wl):

                sub = s[j: j + wl]

                if sub not in gCnt:
                    left = j + wl
                    lCnt = Counter()
                    c = 0

                else:
                    lCnt[sub] += 1

                    if lCnt[sub] <= gCnt[sub]:
                        c += 1
                    else:
                        while lCnt[sub] > gCnt[sub]:
                            w = s[left: left + wl]
                            lCnt[w] -= 1
                            if lCnt[w] < gCnt[sub]:
                                c -= 1
                            left += wl

                    if c == nums:
                        res.append(left)
                        c -= 1
                        lCnt[s[left: left + wl]] -= 1
                        left += wl
        return res

    def doit_1(self, s: str, words):

        from collections import Counter

        res = []
        glcnt = Counter(words)
        totalNums = len(words)
        length, wl = len(s), len(words[0])

        for i in range(wl):

            left, cnt = i, 0
            lcnt = Counter()

            for j in range(i, len(s) - wl + 1, wl):

                w = s[j: j + wl]

                if w not in glcnt:
                    left = j + wl
                    lcnt = Counter()
                    cnt = 0
                    continue

                lcnt[w] += 1
                cnt += 1
                while lcnt[w] > glcnt[w]:
                    w1 = s[left: left + wl]
                    lcnt[w1] -= 1
                    cnt -= 1
                    left += wl

                if cnt == totalNums:
                    res.append(left)
                    w1 = s[left: left + wl]
                    lcnt[w1] -= 1
                    cnt -= 1
                    left += wl

        return res


if __name__ == "__main__":
    
    res = findSubstring().doit("barfoothefoobarman", ["bar", "foo"])

    res = findSubstring().findSubstring("barfoofoobarthefoobarman", ["bar", "foo", "the"])

    pass