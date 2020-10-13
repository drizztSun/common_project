package leetcodeH

/*

363. Max Sum of Rectangle No Larger Than K

Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:

Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
             and 2 is the max number no larger than k (k = 2).
Note:

The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
*/

import (
	"math"
	"sort"
)

func maxSumSubmatrix_binary_search_2(matrix [][]int, k int) int {
	if len(matrix) == 0 {
		return 0
	}
	m, n := len(matrix), len(matrix[0])
	res := math.MinInt32

	for left := 0; left < n; left++ {
		rowSum := make([]int, m)
		for right := left; right < n; right++ {
			for row := 0; row < m; row++ {
				rowSum[row] += matrix[row][right]
			}
			res = Max(res, findTarget(rowSum, k))
			if res == k {
				return k
			}
		}
	}
	return res
}

func Max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func findTarget(arr []int, k int) int {
	sum := arr[0]
	max := arr[0]
	l := len(arr)

	for i := 1; i < l; i++ {
		if sum > 0 {
			sum += arr[i]
		} else {
			sum = arr[i]
		}
		if sum > max {
			max = sum
		}
	}
	if max <= k {
		return max
	}

	max = math.MinInt32
	for left := 0; left < l; left++ {
		sum := 0
		for right := left; right < l; right++ {
			sum += arr[right]
			if sum > max && sum <= k {
				max = sum
			}
			if max == k {
				return k
			}
		}
	}
	return max
}

func maxSumSubmatrix_binary_search(matrix [][]int, k int) int {

	M, N := len(matrix), len(matrix[0])
	ans := math.MinInt32

	search := func(sums []int, k int) int {

		res := []int{0}
		total := 0
		ans := k + 1

		for i := range sums {

			total += sums[i]

			if i := sort.Search(len(res), func(i int) bool { return res[i] >= total-k }); i < len(res) && res[i] >= total-k {
				if ans == k+1 || total-res[i] > ans {
					ans = total - res[i]
				}
			}

			i := sort.Search(len(res), func(i int) bool { return res[i] >= total })
			res = append(res[:i], append([]int{total}, res[i:]...)...)
		}

		return ans
	}

	for i := 0; i < N; i++ {

		sumrage := make([]int, M)

		for j := i; j < N; j++ {
			for z := 0; z < M; z++ {
				sumrage[z] += matrix[z][j]
			}

			r := search(sumrage, k)

			if r == k {
				return r
			}

			if ans < r && r < k {
				ans = r
			}
		}
	}

	return ans
}

func Test_363_MaxSumOfRectangleNoLargerThank() {

	maxSumSubmatrix_binary_search([][]int{[]int{2, 2, -1}}, 0)

	maxSumSubmatrix_binary_search([][]int{[]int{1, 0, 1}, []int{0, -2, 3}}, 2)
}
