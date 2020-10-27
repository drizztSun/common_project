package leetcodem

/*
787. Cheapest Flights Within K Stops

There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops.
If there is no such route, output -1.

Example 1:
Input:
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph looks like this:

The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input:
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph looks like this:

The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.


Constraints:

The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
*/
import (
	"container/heap"
)

type Reachout [][3]int

func (c Reachout) Len() int {
	return len(c)
}

func (c Reachout) Less(i, j int) bool {
	return c[i][0] < c[j][0]
}

func (c Reachout) Swap(i, j int) {
	c[i], c[j] = c[j], c[i]
}

func (c *Reachout) Pop() interface{} {
	old := *c
	n := len(old)
	x := old[n-1]
	*c = old[:n-1]
	return x
}

func (c *Reachout) Push(x interface{}) {
	*c = append(*c, x.([3]int))
}

func findCheapestPrice_heap(n int, flights [][]int, src int, dst int, K int) int {

	graph := make([][]int, n)
	for i := range graph {
		graph[i] = make([]int, n)
	}

	for _, c := range flights {
		graph[c[0]][c[1]] = c[2]
	}

	buf := &Reachout{[3]int{0, src, -1}}
	heap.Init(buf)

	for buf.Len() > 0 {
		cur := heap.Pop(buf).([3]int)
		distance, reachto, step := cur[0], cur[1], cur[2]

		if reachto == dst {
			return distance
		}

		if step+1 <= K {
			for i, v := range graph[reachto] {
				if v != 0 {
					heap.Push(buf, [3]int{distance + v, i, step + 1})
				}
			}
		}
	}

	return -1
}

/*
type node struct {
	stops int
	cost  int
	city  int
}

func findCheapestPrice(n int, flights [][]int, src int, dst int, k int) int {
	graph := createGraph(flights)
	k++
	queue := []*node{{city: src}}
	costs := map[int]int{}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if curr.stops == k {
			continue
		}

		if curr.city == dst {
			costs[dst] = min(costs[dst], curr.cost)
			continue
		}

		for city, price := range graph[curr.city] {
			nc := curr.cost + price
			if v, ok := costs[city]; ok && v < nc {
				continue
			}
			costs[city] = nc
			queue = append(queue, &node{
				stops: curr.stops + 1,
				city:  city,
				cost:  nc,
			})
		}
	}
	if costs[dst] == 0 {
		return -1
	}
	return costs[dst]
}

func min(a, b int) int {
	if a == 0 || b < a {
		return b
	}
	return a
}

func createGraph(flights [][]int) map[int]map[int]int {
	graph := map[int]map[int]int{}
	for _, f := range flights {
		if graph[f[0]] == nil {
			graph[f[0]] = map[int]int{}
		}
		graph[f[0]][f[1]] = f[2]
	}
	return graph
}
*/

func Test_787_CheapestFlightWithinKStops() {

	// findCheapestPrice_heap(3, [][]int{{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1)

	findCheapestPrice_heap(11, [][]int{{0, 3, 3}, {3, 4, 3}, {4, 1, 3}, {0, 5, 1}, {5, 1, 100}, {0, 6, 2}, {6, 1, 100}, {0, 7, 1}, {7, 8, 1}, {8, 9, 1}, {9, 1, 1}, {1, 10, 1}, {10, 2, 1}, {1, 2, 100}}, 0, 2, 4)
}
