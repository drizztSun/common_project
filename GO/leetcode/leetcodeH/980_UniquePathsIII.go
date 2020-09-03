package leetcodeH

/*
980. Unique Paths III

On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.



Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation:
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.
*/

func search_unique_path(grid [][]int, x, y int, num int, seen [][]bool, res *int) {

	if grid[x][y] == 2 {
		if num == 0 {
			*res += 1
		}
		return
	}

	direction := [][]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
	m, n := len(grid), len(grid[0])

	for _, delta := range direction {
		x1, y1 := x+delta[0], y+delta[1]
		if x1 >= 0 && x1 < m && y1 >= 0 && y1 < n && grid[x1][y1] != -1 && !seen[x1][y1] {
			seen[x1][y1] = true
			search_unique_path(grid, x1, y1, num-1, seen, res)
			seen[x1][y1] = false
		}
	}
}

func uniquePathsIII(grid [][]int) int {

	M, N := len(grid), len(grid[0])
	sx, sy, num := 0, 0, 0

	seen := make([][]bool, M)
	for i := 0; i < M; i++ {
		seen[i] = make([]bool, N)
		for j := 0; j < N; j++ {
			seen[i][j] = false

			if grid[i][j] == 0 {
				num++
			} else if grid[i][j] == 1 {
				sx, sy = i, j
			}
		}
	}

	res := 0
	seen[sx][sy] = true
	search_unique_path(grid, sx, sy, num+1, seen, &res)
	return res
}

func Test_980_UniquePathsIII() {

	uniquePathsIII([][]int{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}})
}
