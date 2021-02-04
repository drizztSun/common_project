"""
1405. Longest Happy String

A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.

Given three integers a, b and c, return any string s, which satisfies following conditions:

s is happy and longest possible.
s contains at most a occurrences of the letter 'a', at most b occurrences of the letter 'b' and at most c occurrences of the letter 'c'.
s will only contain 'a', 'b' and 'c' letters.
If there is no such string s return the empty string "".

 

Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.
Example 2:

Input: a = 2, b = 2, c = 1
Output: "aabbc"
Example 3:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It's the only correct answer in this case.
 

Constraints:

0 <= a, b, c <= 100
a + b + c > 0

"""


class LongestDiverseString:

    def doit_(self, a: int, b: int, c: int) -> str:
        m = [['a',a],['b',b],['c',c]]
        m.sort(key = lambda x:-x[1])
        low_bound = max(m[1][1], m[2][1])
        up_bound = m[1][1] + m[2][1]

        if m[0][1] > up_bound:
            ret = (m[0][0] + m[1][0]) * m[1][1] + (m[0][0] + m[2][0]) * m[2][1]
            ret = ret.replace(m[0][0], m[0][0]*2, m[0][1] - up_bound)
            ret += m[0][0] * min(2, m[0][1] - up_bound * 2)
            return ret
        else:
            ret = (m[0][0] + m[1][0] + m[2][0]) * m[2][1]
            ret += (m[0][0] + m[1][0]) * (m[1][1] - m[2][1])
            ret = ret.replace(m[0][0], m[0][0] * 2, m[0][1] - m[1][1])
            ret += m[0][0] * min(2,m[0][1] - m[1][1]*2)
            return ret