package leetcodeH

import (
	"math"
	"sort"
)

type Path struct {
	memo map[[4]int]int
}

func (obj *Path) Search(grid [][]int, i1, j1 int, i2, j2 int) int {

	N, M := len(grid), len(grid[0])
	key := [4]int{i1, j1, i2, j2}
	if v, ok := obj.memo[key]; ok {
		return v
	}

	if i1 == N || j1 == M || i2 == N || j2 == M {
		return -1
	}

	if i1 == N-1 && j1 == M-1 && i2 == N-1 && j2 == M-1 {
		return grid[N-1][M-1]
	}

	if grid[i1][j1] == -1 || grid[i2][j2] == -1 {
		return -1
	}

	rr := obj.Search(grid, i1, j1+1, i2, j2+1)
	rd := obj.Search(grid, i1, j1+1, i2+1, j2)
	dr := obj.Search(grid, i1+1, j1, i2, j2+1)
	dd := obj.Search(grid, i1+1, j1, i2+1, j2)

	res := []int{rr, rd, dr, dd}
	sort.Ints(res)
	out := 0

	if res[3] < 0 {
		out = -1
	} else {
		if i1 == i2 && j1 == j2 {
			out = res[3] + grid[i1][j1]
		} else {
			out = res[3] + grid[i1][j1] + grid[i2][j2]
		}
	}

	obj.memo[key] = out
	return out
}

func cherryPickup(grid [][]int) int {

	memo := Path{memo: make(map[[4]int]int)}

	return int(math.Max(float64(memo.Search(grid, 0, 0, 0, 0)), 0))
}
