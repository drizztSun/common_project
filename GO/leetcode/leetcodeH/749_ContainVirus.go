package leetcodeH

/*
749. Contain Virus

A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

The world is modeled as a 2-D array of cells, where 0 represents uninfected cells, and 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region -- the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night. There will never be a tie.

Can you save the day? If so, what is the number of walls required? If not, and the world becomes fully infected, return the number of walls used.

Example 1:
Input: grid =
[[0,1,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,0]]
Output: 10
Explanation:
There are 2 contaminated regions.
On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:

[[0,1,0,0,0,0,1,1],
 [0,1,0,0,0,0,1,1],
 [0,0,0,0,0,0,1,1],
 [0,0,0,0,0,0,0,1]]

On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
Example 2:
Input: grid =
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output: 4
Explanation: Even though there is only one cell saved, there are 4 walls built.
Notice that walls are only built on the shared boundary of two different cells.
Example 3:
Input: grid =
[[1,1,1,0,0,0,0,0,0],
 [1,0,1,0,1,1,1,1,1],
 [1,1,1,0,0,0,0,0,0]]
Output: 13
Explanation: The region on the left only builds two new walls.
Note:
The number of rows and columns of grid will each be in the range [1, 50].
Each grid[i][j] will be either 0 or 1.
Throughout the described process, there is always a contiguous viral region that will infect strictly more uncontaminated squares in the next round.
*/

func containVirus_dfs(grid [][]int) int {

	M, N := len(grid), len(grid[0])

	makeGroup := func() []map[int]bool {

		groups := make([]map[int]bool, 0)
		visited := make(map[int]bool)

		for i := range grid {
			for j := range grid[i] {

				if grid[i][j] != 1 {
					continue
				}

				if _, ok := visited[i*N+j]; ok {
					continue
				}

				group := make(map[int]bool, 0)
				buf := [][]int{[]int{i, j}}
				visited[i*N+j] = true

				for len(buf) > 0 {

					p := buf[len(buf)-1]
					buf = buf[:len(buf)-1]
					i, j := p[0], p[1]
					group[i*N+j] = true

					for _, c := range [][]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} {
						xx, yy := i+c[0], j+c[1]
						if xx < 0 || xx >= M || yy < 0 || yy >= N {
							continue
						}

						if _, ok := visited[xx*N+yy]; ok || grid[xx][yy] != 1 {
							continue
						}

						buf = append(buf, []int{xx, yy})
						visited[xx*N+yy] = true
					}
				}

				groups = append(groups, group)

			}
		}
		return groups
	}

	expand := func(group map[int]bool) (map[int]bool, int) {

		cnt := make(map[int]bool)
		count := 0

		for k := range group {
			x, y := k/N, k%N
			for _, c := range [][]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} {

				xx, yy := x+c[0], y+c[1]
				if xx < 0 || xx >= M || yy < 0 || yy >= N {
					continue
				}
				if grid[xx][yy] == 0 {
					count++
					cnt[xx*N+yy] = true
				}
			}
		}
		return cnt, count
	}

	groups := makeGroup()

	res := 0

	for len(groups) > 0 {

		walls := make([]map[int]bool, 0)
		max_count, index := 0, 0

		for i, c := range groups {

			infected, count := expand(c)
			walls = append(walls, infected)
			if count > max_count {
				index = i
				max_count = count
			}
		}

		res += max_count

		for c := range groups[index] {
			x, y := c/N, c%N
			grid[x][y] = 2
		}

		walls = append(walls[:index], walls[index+1:]...)

		for _, wall := range walls {
			for c := range wall {
				grid[c/N][c%N] = 1
			}
		}

		groups = makeGroup()
	}

	return res
}

func containVirus_dfs_1(grid [][]int) int {

	M, N := len(grid), len(grid[0])

	makeGroup := func() []map[[2]int]bool {

		groups := make([]map[[2]int]bool, 0)
		visited := make(map[[2]int]bool)

		for i := range grid {
			for j := range grid[i] {

				if grid[i][j] != 1 {
					continue
				}

				if _, ok := visited[[2]int{i, j}]; ok {
					continue
				}

				group := make(map[[2]int]bool, 0)
				buf := [][2]int{[2]int{i, j}}
				visited[[2]int{i, j}] = true

				for len(buf) > 0 {

					p := buf[len(buf)-1]
					buf = buf[:len(buf)-1]
					i, j := p[0], p[1]
					group[[2]int{i, j}] = true

					for _, c := range [][]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}} {
						xx, yy := i+c[0], j+c[1]
						if xx < 0 || xx >= M || yy < 0 || yy >= N {
							continue
						}

						if _, ok := visited[[2]int{xx, yy}]; ok || grid[xx][yy] != 1 {
							continue
						}

						buf = append(buf, [2]int{xx, yy})
						visited[[2]int{xx, yy}] = true
					}
				}

				groups = append(groups, group)

			}
		}
		return groups
	}

	expand := func(group map[[2]int]bool) (map[[2]int]bool, int) {

		cnt := make(map[[2]int]bool)
		count := 0

		for k := range group {
			x, y := k[0], k[1]
			for _, c := range [][]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} {

				xx, yy := x+c[0], y+c[1]
				if xx < 0 || xx >= M || yy < 0 || yy >= N {
					continue
				}
				if grid[xx][yy] == 0 {
					count++
					cnt[[2]int{xx, yy}] = true
				}
			}
		}
		return cnt, count
	}

	groups := makeGroup()

	res := 0

	for len(groups) > 0 {

		walls := make([]map[[2]int]bool, 0)
		max_count, index := 0, 0

		for i, c := range groups {

			infected, count := expand(c)
			walls = append(walls, infected)
			if count > max_count {
				index = i
				max_count = count
			}
		}

		res += max_count

		for c := range groups[index] {
			grid[c[0]][c[1]] = 2
		}

		walls = append(walls[:index], walls[index+1:]...)

		for _, wall := range walls {
			for c := range wall {
				grid[c[0]][c[1]] = 1
			}
		}

		groups = makeGroup()
	}

	return res
}
