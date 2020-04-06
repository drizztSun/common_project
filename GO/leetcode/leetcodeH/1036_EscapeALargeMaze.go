package leetcodeH

/*

1036. Escape a Large Maze

In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.

We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.

Return true if and only if it is possible to reach the target square through a sequence of moves.



Example 1:

Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation:
The target square is inaccessible starting from the source square, because we can't walk outside the grid.
Example 2:

Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation:
Because there are no blocked cells, it's possible to reach the target square.

*/

type DFSBase struct {
	startX int
	startY int
	points map[int]int
}

func (host *DFSBase) locked(x int, y int) bool {
	if x < 0 {
		return true
	}
	if x > 1000000 {
		return true
	}
	if y < 0 {
		return true
	}
	if y > 1000000 {
		return true
	}
	a := x - host.startX
	if a < 0 {
		a = -a
	}
	b := y - host.startY
	if b < 0 {
		b = -b
	}
	if a+b > 210 {
		return false
	}

	z := 1000001*x + y
	_, ok := host.points[z]
	if ok {
		return true
	}
	host.points[z] = 1
	return host.locked(x, y-1) && host.locked(x, y+1) && host.locked(x-1, y) && host.locked(x+1, y)
}

func isEscapePossible(blocked [][]int, source []int, target []int) bool {
	var b DFSBase
	b.points = make(map[int]int)
	n := len(blocked)
	for i := 0; i < n; i++ {
		if blocked[i][0] == source[0] && blocked[i][1] == source[1] {
			return false
		}
		if blocked[i][0] == target[0] && blocked[i][1] == target[1] {
			return false
		}
		b.points[1000001*blocked[i][0]+blocked[i][1]] = 1
	}
	b.startX = source[0]
	b.startY = source[1]

	if b.locked(source[0], source[1]) {
		_, ok := b.points[target[0]*1000001+target[1]]
		return ok
	}

	b.points = make(map[int]int)
	for i := 0; i < n; i++ {
		if blocked[i][0] == source[0] && blocked[i][1] == source[1] {
			return false
		}
		if blocked[i][0] == target[0] && blocked[i][1] == target[1] {
			return false
		}
		b.points[1000001*blocked[i][0]+blocked[i][1]] = 1
	}
	b.startX = target[0]
	b.startY = target[1]

	return !b.locked(target[0], target[1])

}
