package leetcodeH

/*
85. Maximal Rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6

*/

func maximalRectangle(matrix [][]byte) int {

	M, N := len(matrix), len(matrix[0])
	dp := make([][][]int, M)
	res := 0

	for i := 0; i < M; i++ {
		dp[i] = make([]int, N)

		for j := 0; j < N; j++ {
			dp[i][j] = []int{0, 0}

			if matrix[i][j] == 1 {
				dp[i][j] = []int{1, 1}

				if res < dp[i][j][0]*dp[i][j][1] {
					res = dp[i][j][0] * dp[i][j][1]
				}
			}

		}
	}

	return res
}

func maximalRectangle_dp(matrix [][]byte) int {

	if len(matrix) == 0 {
		return 0
	}

	m, n := len(matrix), len(matrix[0])
	high, left, right := make([]int, n), make([]int, n), make([]int, n)
	for i := 0; i < n; i++ {
		right[i] = n
	}
	maxArea := 0

	for i := 0; i < m; i++ {

		for j := 0; j < n; j++ {
			high[j]++
			if matrix[i][j] == '0' {
				high[j] = 0
			}
		}

		curleft, curright := 0, n

		for j := 0; j < n; j++ {
			if matrix[i][j] == '1' {
				if left[j] < curleft {
					left[j] = curleft
				}
			} else {
				left[j], curleft = 0, j+1
			}
		}

		for j := n - 1; j >= 0; j-- {
			if matrix[i][j] == '1' {
				if right[j] > curright {
					right[j] = curright
				}
			} else {
				right[j], curright = n, j
			}
		}

		for j := 0; j < n; j++ {
			if maxArea < (right[j]-left[j])*high[j] {
				maxArea = (right[j] - left[j]) * high[j]
			}
		}
	}

	return maxArea
}

func maximalRectangle_dp_stack(matrix [][]byte) int {

	if len(matrix) == 0 {
		return 0
	}

	heights := make([]int, len(matrix[0])+2)
	heights[0], heights[len(matrix[0])+1] = 0, 0
	maxArea := 0

	for i := range matrix {

		for j := 0; j < len(matrix[0]); j++ {
			if matrix[i][j] == '1' {
				heights[j+1]++
			} else {
				heights[j+1] = 0
			}
		}

		st := make([]int, 0)

		for j := 0; j < len(heights); j++ {

			for len(st) > 0 && heights[j] < heights[st[len(st)-1]] {
				h := heights[st[len(st)-1]]
				st = st[:len(st)-1]
				if maxArea < h*(j-st[len(st)-1]-1) {
					maxArea = h * (j - st[len(st)-1] - 1)
				}
			}

			st = append(st, j)
		}
	}

	return maxArea
}

func Test_85_MaximalRectangle() {

	maximalRectangle_dp_stack([][]byte{{'1', '0', '1', '0', '0'},
		{'1', '0', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0'}})
}
