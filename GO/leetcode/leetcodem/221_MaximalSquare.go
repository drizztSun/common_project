package leetcodem

/*

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4

*/

func maximalSquare(matrix [][]byte) int {

	if len(matrix) == 0 {
		return 0
	}

	minInt := func(a, b int) int {
		if a > b {
			return b
		}
		return a
	}

	m, n := len(matrix), len(matrix[0])
	dp := make([][]int, m)
	res := 0

	for i := range dp {
		dp[i] = make([]int, n)
	}

	for i := range dp {
		for j := range dp[i] {

			if (i == 0 || j == 0) && matrix[i][j] == '1' {
				dp[i][j] = 1
			} else if matrix[i][j] == '1' {
				dp[i][j] = 1 + minInt(minInt(dp[i-1][j-1], dp[i-1][j]), minInt(dp[i-1][j-1], dp[i][j-1]))
			} else {
				dp[i][j] = 0
			}

			if res < dp[i][j] {
				res = dp[i][j]
			}
		}
	}

	return res * res
}
