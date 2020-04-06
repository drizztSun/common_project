package leetcodem

/*
1034. Coloring A Border

Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.

Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.

The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component,
or on the boundary of the grid (the first or last row or column).

Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.



Example 1:

Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
Output: [[3, 3], [3, 2]]
Example 2:

Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
Output: [[1, 3, 3], [2, 3, 3]]
Example 3:

Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]

*/

func colorBorder_search(grid [][]int, x int, y int, orig int, color int) bool {

	M, N := len(grid), len(grid[0])

	if x < 0 || x == M || y < 0 || y == M {
		return false
	}

	if grid[x][y] != orig {
		return false
	}

	if x == 0 || x == M-1 || y == 0 || y == N-1 {
		grid[x][y] = color
	} else {
		grid[x][y] = color
	}

	return true
}

func colorBorder(grid [][]int, r0 int, c0 int, color int) [][]int {

	colorBorder_search(grid, r0, c0, grid[r0][c0], color)
	return grid
}

func colorBorder1(grid [][]int, r0 int, c0 int, color int) [][]int {

	M, N := len(grid), len(grid[0])
	buf := make([][]int, 0)
	seen, border := make(map[int]struct{}), make(map[int]struct{})
	direct := [][]int{[]int{1, 0}, []int{-1, 0}, []int{0, 1}, []int{0, -1}}
	buf = append(buf, []int{r0, c0})

	for len(buf) != 0 {

		c := buf[len(buf)-1]
		buf = buf[:len(buf)-1]

		for _, n := range direct {
			x, y := c[0]+n[0], c[1]+n[1]
			if x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == grid[r0][c0] {
				if _, ok := seen[x*N+y]; !ok {
					buf = append(buf, []int{x, y})
					seen[x*N+y] = struct{}{}
				}
			} else {
				border[c[0]*N+c[1]] = struct{}{}
			}
		}
	}

	for k, _ := range border {
		x, y := k/N, k%N
		grid[x][y] = color
	}

	return grid
}

func Test_1034_ColoringABorder() {

	colorBorder1([][]int{[]int{1, 1, 1}, []int{1, 1, 1}, []int{1, 1, 1}}, 1, 1, 2)
}
