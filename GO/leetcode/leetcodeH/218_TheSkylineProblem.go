package leetcodeH

import (
	"container/heap"
	"sort"
)

/*

 */

type HeightQueue [][]int

func (i HeightQueue) Less(a, b int) bool {
	return i[a][0] < i[b][0] || (i[a][0] == i[b][0] && i[a][1] < i[b][1])
}

func (i HeightQueue) Len() int {
	return len(i)
}

func (i HeightQueue) Swap(a, b int) {
	i[a][0], i[b][0] = i[b][0], i[a][0]
	i[a][1], i[b][1] = i[b][1], i[a][1]
}

func (i *HeightQueue) Push(a interface{}) {
	*i = append(*i, a.([]int))
}

func (i *HeightQueue) Pop() interface{} {
	old := *i
	n := len(old)

	x := old[n-1]
	*i = old[:n-1]
	return x
}

func getSkyline(buildings [][]int) [][]int {

	skyline := make([][]int, 0)
	highQueue := make(HeightQueue, 0)
	i := 0
	heap.Init(&highQueue)

	for i < len(buildings) || len(highQueue) > 0 {

		x := 0

		if len(highQueue) == 0 || (i < len(buildings) && buildings[i][0] <= -highQueue[0][1]) {
			x = buildings[i][0]
			for i < len(buildings) && buildings[i][0] <= x {
				heap.Push(&highQueue, []int{-buildings[i][2], -buildings[i][1]})
				i++
			}

		} else {
			x = -highQueue[0][1]
			for highQueue.Len() > 0 && -highQueue[0][1] <= x {
				heap.Pop(&highQueue)
			}
		}

		height := highQueue.Len()
		if height != 0 {
			height = -highQueue[0][0]
		}

		if len(skyline) == 0 || height != skyline[len(skyline)-1][1] {
			skyline = append(skyline, []int{x, height})
		}
	}

	return skyline
}

// code

func getSkyline1(buildings [][]int) [][]int {
	points := make([]*RoofPoint, len(buildings)*2)
	rightToLeftMap := make(map[*RoofPoint]*RoofPoint)

	for i := 0; i < len(buildings); i++ {
		points[i*2] = &RoofPoint{IsLeft: true, X: buildings[i][0], Height: buildings[i][2]}
		points[1+i*2] = &RoofPoint{IsLeft: false, X: buildings[i][1], Height: buildings[i][2]}
		rightToLeftMap[points[1+i*2]] = points[i*2]
	}
	sort.Sort(ByXAsc(points))

	pq := make(PQ, 0)
	heap.Init(&pq)

	var result [][]int
	for i := 0; i < len(points); i++ {
		point := points[i]
		if point.IsLeft {
			heap.Push(&pq, point)
			if len(result) == 0 {
				result = append(result, []int{point.X, point.Height})
				continue
			}

			highest := pq[0]
			if result[len(result)-1][1] >= highest.Height {
				continue
			}

			if result[len(result)-1][0] == point.X {
				result[len(result)-1][1] = highest.Height

				if len(result) > 1 && result[len(result)-2][1] == highest.Height {
					result = result[:len(result)-1]
				}
			} else {
				result = append(result, []int{point.X, highest.Height})
			}
			continue
		}

		heap.Remove(&pq, rightToLeftMap[point].HeapIdx)

		if len(pq) == 0 {
			if result[len(result)-1][0] < point.X {
				result = append(result, []int{point.X, 0})
			} else {
				result[len(result)-1][1] = 0
			}
			continue
		}

		highest := pq[0]
		if result[len(result)-1][1] > highest.Height {
			if result[len(result)-1][0] < point.X {
				result = append(result, []int{point.X, highest.Height})
			} else {
				result[len(result)-1][1] = highest.Height
			}
		}
	}
	return result
}

type RoofPoint struct {
	HeapIdx int
	IsLeft  bool
	X       int
	Height  int
}

type ByXAsc []*RoofPoint

func (points ByXAsc) Len() int {
	return len(points)
}

func (points ByXAsc) Swap(i, j int) {
	points[i], points[j] = points[j], points[i]
}

func (points ByXAsc) Less(i, j int) bool {
	return points[i].X < points[j].X
}

type PQ []*RoofPoint

func (points PQ) Len() int {
	return len(points)
}

func (points PQ) Swap(i, j int) {
	points[i], points[j] = points[j], points[i]
	points[i].HeapIdx = i
	points[j].HeapIdx = j
}

func (points PQ) Less(i, j int) bool {
	if points[i].Height == points[j].Height {
		return !points[i].IsLeft
	}
	return points[i].Height > points[j].Height
}

func (points *PQ) Push(item interface{}) {
	newP := item.(*RoofPoint)
	newP.HeapIdx = len(*points)
	*points = append(*points, newP)
}

func (points *PQ) Pop() interface{} {
	tmp := (*points)[len(*points)-1]
	tmp.HeapIdx = -1
	*points = (*points)[:len(*points)-1]
	return tmp
}

/*
func main() {

	fmt.Println("Hello world")
	// [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]

	buildings := [][]int{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}}

	res := getSkyline(buildings)

	for _, v := range res {
		fmt.Print("%d, ", v)
	}
}
*/
