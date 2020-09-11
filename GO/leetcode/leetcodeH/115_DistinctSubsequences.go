package leetcodeH

/*
115. Distinct Subsequences

Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It's guaranteed the answer fits on a 32-bit signed integer.

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
	^^^

*/

func numDistinct_dp(s string, t string) int {

	m, n := len(s), len(t)

	dp := make([][2]int, m+1)
	for j := 0; j <= m; j++ {
		dp[j] = [2]int{1, 0}
	}

	for i := 1; i <= n; i++ {

		last, cur := (i+1)%2, i%2
		dp[0][cur] = 0

		for j := 1; j <= m; j++ {

			dp[j][cur] = dp[j-1][cur]
			if t[i-1] == s[j-1] {
				dp[j][cur] += dp[j-1][last]
			}
		}

	}
	return dp[m][n%2]
}
