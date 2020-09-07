package leetcodeH

/*
72. Edit Distance

Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character
Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/

func minDistance_dp(word1 string, word2 string) int {

	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	M, N := len(word1), len(word2)
	dp := make([][]int, M+1)
	for i := 0; i <= M; i++ {
		dp[i] = make([]int, N+1)
		dp[i][0] = i
	}

	for j := 1; j <= N; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= M; i++ {
		for j := 1; j <= N; j++ {

			// if not same change it, Replace := dp[i-1][j-1] + 1 or 0
			// Delete: dp[i-1][j], Insert: dp[i][j-1]
			replaced := 0
			if word1[i-1] != word2[j-1] {
				replaced = 1
			}

			dp[i][j] = min(dp[i-1][j-1]+replaced, min(dp[i-1][j], dp[i][j-1])+1)
		}
	}

	return dp[M][N]
}

func minDistance_dp_lowmomery(word1 string, word2 string) int {

	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	M := len(word1)
	dp := make([]int, M+1)
	for i := 0; i <= M; i++ {
		dp[i] = i
	}

	for j := 1; j <= len(word2); j++ {
		dpl := make([]int, M+1)
		dpl[0] = j

		for i := 1; i <= M; i++ {

			replaced := 0
			if word1[i-1] != word2[j-1] {
				replaced = 1
			}

			dpl[i] = min(dp[j-1]+replaced, min(dp[j], dpl[j-1])+1)
		}

		dp = dpl
	}
	return dp[M]
}

func test_72_minDistance() {

	minDistance_dp("horse", "ros")

	minDistance_dp("intention", "execution")
}
