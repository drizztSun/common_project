package leetcodeH

/*

 996. Number of Squareful Arrays

 Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.

 Return the number of permutations of A that are squareful.  Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].

 Example 1:

 Input: [1,17,8]
 Output: 2
 Explanation:
 [1,8,17] and [17,8,1] are the valid permutations.
 Example 2:

 Input: [2,2,2]
 Output: 1

*/

import (
	"math"
)

func dfs_search(graph map[int][]int, cnt map[int]int, x, steps int) int {

	cnt[x] -= 1
	ans := 1
	if steps != 0 {
		ans = 0
		for _, y := range graph[x] {
			if cnt[y] > 0 {
				ans += dfs_search(graph, cnt, y, steps-1)
			}
		}
	}
	cnt[x] += 1
	return ans
}

func numSquarefulPerms(A []int) int {

	cnt := make(map[int]int)
	for _, v := range A {
		cnt[v]++
	}

	graph := make(map[int][]int)
	for x := range cnt {
		for y := range cnt {
			base := int(math.Sqrt(float64(x + y)))
			if base*base == x+y {
				graph[x] = append(graph[x], y)
			}
		}
	}

	ans := 0
	for v, _ := range cnt {
		ans += dfs_search(graph, cnt, v, len(A)-1)
	}
	return ans
}

func isSquare(x int) bool {
	r := int(math.Sqrt(float64(x)))
	return r*r == x
}

func numSquarefulPerms1(A []int) int {
	size := len(A)
	count := make(map[int]int, size)
	cond := make(map[int][]int, size)
	for _, i := range A {
		count[i]++
	}
	for x := range count {
		for y := range count {
			if isSquare(x + y) {
				cond[x] = append(cond[x], y)
			}
		}
	}
	cnt := 0
	var dfs func(int, int)
	dfs = func(x, left int) {
		if left == 0 {
			cnt++
			return
		}
		count[x]--
		for _, y := range cond[x] {
			if count[y] > 0 {
				dfs(y, left-1)
			}
		}
		count[x]++
	}

	for x := range count {
		dfs(x, size-1)
	}
	return cnt
}

func Test_996_NumberOfSquarefulArrays() {

	numSquarefulPerms([]int{1, 17, 8})

	numSquarefulPerms1([]int{1, 17, 8})

	numSquarefulPerms([]int{2, 2, 2})

	numSquarefulPerms1([]int{2, 2, 2})
}
