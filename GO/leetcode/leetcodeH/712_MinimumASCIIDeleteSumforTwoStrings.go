package leetcodeH

/*

# 712. Minimum ASCII Delete Sum for Two Strings

# Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

# Example 1:
# Input: s1 = "sea", s2 = "eat"
# Output: 231
# Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
# Deleting "t" from "eat" adds 116 to the sum.
# At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

# Example 2:
# Input: s1 = "delete", s2 = "leet"
# Output: 403
# Explanation: Deleting "dee" from "delete" to turn the string into "let",
# adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
# At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
# If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

*/

func minimumDeleteSum(s1 string, s2 string) int {

	m, n := len(s1), len(s2)
	dp := make([][]int, m+1)
	for i := range dp {
		dp[i] = make([]int, n+1)
	}

	dp[0][0] = 0

	for i := 0; i < m; i++ {
		dp[i+1][0] = int(s1[i]) + dp[i][0]
	}

	for j := 0; j < n; j++ {
		dp[0][j+1] = int(s2[j]) + dp[0][j]
	}

	for i := 1; i < len(dp); i++ {
		for j := 1; j < len(dp[0]); j++ {

			a := dp[i-1][j-1]
			if s1[i-1] != s2[j-1] {
				a += int(s1[i-1]) + int(s2[j-1])
			}

			if a > dp[i-1][j]+int(s1[i-1]) {
				a = dp[i-1][j] + int(s1[i-1])
			}

			if a > dp[i][j-1]+int(s2[j-1]) {
				a = dp[i][j-1] + int(s2[j-1])
			}

			dp[i][j] = a
		}
	}

	return dp[m][n]
}

func minimumDeleteSum1(s1 string, s2 string) int {
	len1, len2 := len(s1), len(s2)
	dp := make([]int, len2+1)
	for i := range dp {
		dp[i] = 0
	}

	for i := 1; i < len2+1; i++ {
		dp[i] = dp[i-1] + int(s2[i-1])
	}

	for i := 1; i < len1+1; i++ {
		temp_j_one := dp[0]
		dp[0] += int(s1[i-1])
		for j := 1; j < len2+1; j++ {
			temp_j := dp[j]
			if s1[i-1] == s2[j-1] {
				dp[j] = temp_j_one
			} else {
				dp[j] = min(temp_j+int(s1[i-1]), dp[j-1]+int(s2[j-1]))
			}
			temp_j_one = temp_j
		}
	}
	return dp[len2]
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
