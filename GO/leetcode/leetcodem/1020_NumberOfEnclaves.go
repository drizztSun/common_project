package leetcodem

/*

1020. Number of Enclaves

Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.

 

Example 1:

Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: 
There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
Example 2:

Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: 
All 1s are either on the boundary or can reach the boundary.

*/


func numEnclaves_search(A [][]int, x int, y int) {

	M, N := len(A), len(A[0])
	if (x < 0 || x == M || y < 0 || y == N) || (A[x][y] == 0) {
		return
	}

	A[x][y] = 0

	numEnclaves_search(A, x - 1, y)
	numEnclaves_search(A, x + 1, y)
	numEnclaves_search(A, x, y - 1)
	numEnclaves_search(A, x, y + 1)
}

func numEnclaves(A [][]int) int {

	M, N := len(A), len(A[0])

	for i := 0; i < M; i++ {
		numEnclaves_search(A, i, 0)
		numEnclaves_search(A, i, N - 1)
	}

	for j := 0; j < N; j++ {
		numEnclaves_search(A, 0, j)
		numEnclaves_search(A, M-1, j)
	}

	ans := 0
	for i := 0; i < M; i++ {
		for j := 0; j < N; j++ {
			if A[i][j] == 1 {
				ans++
			}
		}
	}

	return ans
}

func numEnclaves1(A [][]int) int {

	edges := make([]int, 0)
	M, N := len(A), len(A[0])
	cnt := 0

	for i := 0; i < M; i++ {
		for j := 0; j < N; j++ {
			if A[i][j] == 1 {
				cnt++
				if i == 0 || i == M-1 || j == 0 || j == N-1 {
					edges = append(edges, i * N + j)
				}
			}
		}
	}

	for len(edges) != 0 {

		n := edges[len(edges) - 1]
		edges = edges[:len(edges) - 1]
		buf := []int{n}

		for len(buf) != 0 {

			xn := buf[len(buf)-1]
			buf = buf[:len(buf)-1]
			x, y := xn / N, xn % N
			if A[x][y] == 1 {
				A[x][y] = 0
				cnt--
				for _, v := range [][]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} {
					x0, y0 := x + v[0], y + v[1]
					if x0 >= 0 && x0 < M && y0 >= 0 && y0 < N && A[x0][y0] == 1 {
						buf = append(buf, x0 * N + y0)
					}
				}
			}
		}
	}

	return cnt
}

func Test_1020_NumberOfEnclaves() {

	numEnclaves1([][]int{
		{0,0,0,0},
		{1,0,1,0},
		{0,1,1,0},
		{0,0,0,0},
	})

	numEnclaves1([][]int{
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,0,0},
	})
}