package leetcodem

/*
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

*/

import "strconv"

func numDecodings(s string) int {
	if s[0] == '0' {
		return 0
	}

	i1, i2 := 1, 1

	for i := 1; i < len(s); i++ {

		cur := 0
		tens, _ := strconv.ParseInt(s[i-1:i+1], 10, 32)

		if s[i] == '0' && tens > 26 {
			return 0
		}

		if s[i] != '0' {
			cur += i1
		}

		if i != 0 && tens >= 10 && tens <= 26 {
			cur += i2
		}

		i1, i2 = cur, i1
	}

	return i1
}

func Test_91_numDecodings() {

	numDecodings("0")

	numDecodings("1")

	numDecodings("27")

	numDecodings("150")

	numDecodings("226")

	numDecodings("100")
}
