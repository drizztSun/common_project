#!/usr/bin/env python3
from typing import List
 
# Author: Huahua
 
# LC 28

# nxt array is a suffix array, and DP thought. 
# nxt[i] = [j] it means there is a j length str from 0 s[0:j] equal to j length substr end by i, exclusing i.
# nxt[i] = j => s[0:j] == s[i-j-1:i]
# so if p[j] != p[i], the suffix end by i, should be tried out to find on nxt[nxt[j]]. 
# it means there is length jj where nxt[0:jj]= ii, s[0:jj] == s[j-jj+1:j], we will continue to try until jj == 0


def Build(p: str) -> List[int]:
    m = len(p)
    nxt = [0, 0]
    j = 0
    for i in range(1, m):
        while j > 0 and p[i] != p[j]:
            j = nxt[j]
        if p[i] == p[j]:
            j += 1
        nxt.append(j)
    return nxt
 
 
def Match(s: str, p: str) -> List[int]:
    n, m = len(s), len(p)
    nxt = Build(p)
    ans = []
    j = 0
    for i in range(n):
        while j > 0 and s[i] != p[j]:
            j = nxt[j]
        if s[i] == p[j]:
            j += 1
        if j == m:
            ans.append(i - m + 1)
            j = nxt[j]
    return ans
 
 
def CheckEQ(actual, expected):
    if actual != expected:
        print('actual: %s, expected: %s' % (actual, expected))
    else:
        print('Pass')
 
 
if __name__ == "__main__":
    
    CheckEQ(Build("ABCDABD"), [0, 0, 0, 0, 0, 1, 2, 0])
    CheckEQ(Build("AB"), [0, 0, 0])
    CheckEQ(Build("A"), [0, 0])
    CheckEQ(Build("AA"), [0, 0, 1])
    CheckEQ(Build("AAAA"), [0, 0, 1, 2, 3])
    CheckEQ(Build("AABA"), [0, 0, 1, 0, 1])
    CheckEQ(Match("ABC ABCDAB ABCDABCDABDE", "ABCDABD"), [15])
    CheckEQ(Match("ABC ABCDAB ABCDABCDABDE", "AB"), [0, 4, 8, 11, 15, 19])
    CheckEQ(Match("ABC ABCDAB ABCDABCDABDE", "B"), [1, 5, 9, 12, 16, 20])
    CheckEQ(Match("AAAAA", "A"), [0, 1, 2, 3, 4])
    CheckEQ(Match("AAAAA", "AA"), [0, 1, 2, 3])
    CheckEQ(Match("AAAAA", "AAAA"), [0, 1])
    CheckEQ(Match("AAAAA", "AAAAA"), [0])
    CheckEQ(Match("AABAABA", "AABA"), [0, 3])