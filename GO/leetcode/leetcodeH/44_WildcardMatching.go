package leetcodeH

/*
44. Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false

*/

func isWildCastMatch_dp2(s string, p string) bool {

	M, N := len(s)+1, len(p)+1
	dp := make([][]bool, M)

	for i := 0; i < M; i++ {
		dp[i] = make([]bool, N)
		for j := 0; j < N; j++ {
			dp[i][j] = false
		}
	}

	dp[0][0] = true
	for i := 1; i < N; i++ {
		dp[0][i] = dp[0][i-1] && p[i-1] == '*'
	}

	for i := 1; i < M; i++ {

		for j := 1; j < N; j++ {

			if p[j-1] != '*' {
				dp[i][j] = dp[i-1][j-1] && (p[j-1] == '?' || p[j-1] == s[i-1])
			} else {
				dp[i][j] = dp[i-1][j] || dp[i][j-1]
			}
		}
	}

	return dp[M-1][N-1]
}

func isWildCastMatch_dp1(s string, p string) bool {

	M, N := len(s)+1, len(p)+1
	dp := make([]bool, M)
	dp[0] = true

	for i := 1; i < N; i++ {

		if p[i-1] == '*' {
			for j := 1; j < M; j++ {
				// j - 1 is that * matchs 0, dp[i][j] = dp[i][j-1]
				// j is that * match 1, dp[i][j] = dp[i-1][j]
				dp[j] = dp[j] || dp[j-1]
			}
		} else {
			// reverse iter, because dp[i][j] needs dp[i-1][j-1].
			// if it is not reverse, it will calculate dp[i][j-1] first, and then cover the dp[i-1][j-1]
			for j := M - 1; j >= 1; j-- {
				// when (s[0..i-1], p[0..j-1]) is matched, and (s[i], p[j]) is matched
				dp[j] = dp[j-1] && (p[i-1] == s[j-1] || p[i-1] == '?')
			}
		}

		// init dp[0] is s[0:] if match p[:i-1]
		dp[0] = dp[0] && p[i-1] == '*'
	}

	return dp[len(s)]
}

func Test_44_WildCastMatching() {

	isWildCastMatch("acdcb", "a*c?b")
}
