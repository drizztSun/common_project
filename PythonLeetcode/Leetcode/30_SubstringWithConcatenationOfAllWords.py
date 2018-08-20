import os

import collections

# 30. Substring with Concatenation of All Words

# You are given a string, s, and a list of words, words, that are all of the same length. 
# Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

# For example, given:
# s: "barfoothefoobarman"
# words: ["foo", "bar"]

# You should return the indices: [0,9].
# (order does not matter).


class findSubstring(object):
    def doit1(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        nums, length, wl = len(words), len(s), len(words[0])

        if length < wl * nums:
            return []

        # wc = Counter(words)
        wc = {}
        for c in words:
            wc.setdefault(c, 0)
            wc[c] += 1

        ans = []

        for i in range(wl):
            
            left, count = i, 0
            tDict = dict()
            for j in range(i, length-wl+1, wl):
    
                substr = s[j: j+wl]

                if substr in wc:
                    tDict.setdefault(substr, 0)
                    tDict[substr] += 1

                    if tDict[substr] <= wc[substr]:
                        count += 1
                    else:
                        while tDict[substr] > wc[substr]:
                            b = s[left: left+wl]
                            tDict[b] -= 1
                            if tDict[b] < wc[b]:
                                count -= 1
                            left += wl
                    
                    # generate result
                    if count == nums:
                        ans.append(left)
                        count -= 1
                        tDict[s[left: left+wl]] -= 1
                        left += wl

                else :
                    tDict.clear()
                    count = 0
                    left = j + wl

        return ans

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
        
        if len(s) < nums * wl:
            return []

        for i in range(wl):
            
            lCnt = Counter()
            left, c = i, 0
            for j in range(i, len(s) - wl + 1, wl):
                
                sub = s[j : j + wl]
                
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



if __name__ == "__main__":
    
    res = findSubstring().doit("barfoothefoobarman", ["bar", "foo"])

    res = findSubstring().doit("barfoofoobarthefoobarman", ["bar", "foo", "the"])

    pass