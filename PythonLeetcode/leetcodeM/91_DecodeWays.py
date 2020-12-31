"""
91. Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

"""


class NumDecodings:

    def doit_dp(self, s: str) -> bool:

        i1, i2 = 1, 1

        for i in range(0, len(s)):
            cur = 0

            if s[i] == '0' and (i == 0 or int(s[i-1:i+1]) > 26):
                return 0

            if s[i] != '0':
                cur = i1

            if i > 0 and 26 >= int(s[i-1:i+1]) >= 10:
                cur += i2

            i1, i2 = cur, i1

        return i1


if __name__ == '__main__':

    NumDecodings().doit_dp("01")

    NumDecodings().doit_dp("27")

    NumDecodings().doit_dp("101")

    NumDecodings().doit_dp("100")

    NumDecodings().doit_dp("150")

    NumDecodings().doit_dp("12")

    NumDecodings().doit_dp("226")