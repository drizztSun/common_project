package leetcodem

/*
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.

*/

func minPathSum_dp(grid [][]int) int {

	M, N := len(grid), len(grid[0])
	dp := make([][]int, M)
	for i := 0; i < M; i++ {
		dp[i] = make([]int, N)
	}

	for i := 0; i < M; i++ {
		for j := 0; j < N; j++ {

			dp[i][j] += grid[i][j]

			if i == 0 && j == 0 {
				continue
			} else if i == 0 {
				dp[i][j] += dp[i][j-1]
			} else if j == 0 {
				dp[i][j] += dp[i-1][j]
			} else {
				if dp[i-1][j] < dp[i][j-1] {
					dp[i][j] += dp[i-1][j]
				} else {
					dp[i][j] += dp[i][j-1]
				}
			}
		}
	}

	return dp[M-1][N-1]
}

func Test_64_MinimumPathSum() {

	minPathSum_dp([][]int{
		[]int{1, 3, 1},
		[]int{1, 5, 1},
		[]int{4, 2, 1},
	})
}
