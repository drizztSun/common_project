package leetcodeH

/*
778. Swim in Rising Water

On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

Example 1:

Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:

Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
Note:

2 <= N <= 50.
grid[i][j] is a permutation of [0, ..., N*N - 1].

*/
import (
	"container/heap"
)

type baseheap [][3]int

func (c baseheap) Len() int {
	return len(c)
}

func (c baseheap) Less(i, j int) bool {
	return c[i][0] < c[j][0]
}

func (c baseheap) Swap(i, j int) {
	c[i], c[j] = c[j], c[i]
}

func (c *baseheap) Push(x interface{}) {
	*c = append(*c, x.([3]int))
}

func (c *baseheap) Pop() interface{} {
	old := *c
	n := len(old)
	x := old[n-1]
	*c = old[:n-1]
	return x
}

func swimInWater_heap(grid [][]int) int {

	M, N := len(grid), len(grid[0])
	buf := &baseheap{[3]int{grid[0][0], 0, 0}}
	heap.Init(buf)
	seen := make([][]bool, M)
	for i := range seen {
		seen[i] = make([]bool, N)
	}
	height := 0

	for buf.Len() > 0 {
		c := heap.Pop(buf).([3]int)

		if height < c[0] {
			height = c[0]
		}

		if c[1] == M-1 && c[2] == N-1 {
			return height
		}

		for _, delta := range [][2]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} {
			x, y := c[1]+delta[0], c[2]+delta[1]

			if x >= 0 && x < M && y >= 0 && y < N && !seen[x][y] {
				heap.Push(buf, [3]int{grid[x][y], x, y})
				seen[x][y] = true
			}
		}
	}

	return height
}

func Test_778_SwimInRisingWater() {

	swimInWater_heap([][]int{[]int{0, 2}, []int{1, 3}})
}
