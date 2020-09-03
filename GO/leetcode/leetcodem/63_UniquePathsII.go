package leetcodem

/*

63. Unique Paths II

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:

Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

*/

func uniquePathsWithObstacles_1(obstacleGrid [][]int) int {
	o := obstacleGrid

	if o[0][0] == 1 {
		return 0
	}
	dp := make([]int, len(o[0]))
	dp[0] = 1

	for i := 1; i < len(o[0]); i++ {
		if o[0][i] != 1 {
			dp[i] = dp[i-1]
		} else {
			dp[i] = 0
		}
	}

	for j := 1; j < len(o); j++ {
		r := o[j]

		if r[0] == 1 {
			dp[0] = 0
		}

		for i := 1; i < len(r); i++ {
			if r[i] == 1 {
				dp[i] = 0
			} else {
				dp[i] = dp[i] + dp[i-1]
			}
		}
	}

	return dp[len(dp)-1]
}

func uniquePathsWithObstacles_2(grid [][]int) int {
	m := len(grid)
	if m == 0 {
		return 0
	}
	n := len(grid[0])

	dp := make([][]int, m)

	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)

		for j := 0; j < n; j++ {

			if grid[i][j] == 1 {
				dp[i][j] = 0
			} else {

				if i == 0 && j == 0 {
					dp[i][j] = 1
				} else {
					if i > 0 {
						dp[i][j] += dp[i-1][j]
					}
					if j > 0 {
						dp[i][j] += dp[i][j-1]
					}
				}
			}
		}

	}

	return dp[m-1][n-1]
}