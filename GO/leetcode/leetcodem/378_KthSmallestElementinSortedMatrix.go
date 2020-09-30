package leetcodem

/*
378. Kth Smallest Element in a Sorted Matrix

Given a n x n matrix where each of the rows and columns are sorted in ascending order,
find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.
*/

import (
	"container/heap"
)

type kthNode [][3]int

func (this kthNode) Len() int {
	return len(this)
}

func (this kthNode) Less(i, j int) bool {
	return this[i][0] < this[j][0]
}

func (this kthNode) Swap(i, j int) {
	this[i], this[j] = this[j], this[i]
}

func (this *kthNode) Pop() interface{} {

	old := *this
	n := len(old)

	x := old[n-1]
	*this = old[:n-1]
	return x
}

func (this *kthNode) Push(x interface{}) {
	*this = append(*this, x.([3]int))
}

func kthSmallest_heap(matrix [][]int, k int) int {
	hnodes := &kthNode{[3]int{matrix[0][0], 0, 0}}
	heap.Init(hnodes)
	res := 0

	for ; k > 0; k-- {

		c := heap.Pop(hnodes).([3]int)
		num, i, j := c[0], c[1], c[2]
		res = num

		if j+1 < len(matrix[0]) {
			heap.Push(hnodes, [3]int{matrix[i][j+1], i, j + 1})
		}

		if j == 0 && i+1 < len(matrix) {
			heap.Push(hnodes, [3]int{matrix[i+1][j], i + 1, j})
		}
	}

	return res
}

func kthSmallest_binary_search(matrix [][]int, k int) int {
	n := len(matrix)
	low := matrix[0][0]
	high := matrix[n-1][n-1]
	for low < high {
		mid := (low + high) >> 1
		if countKthSmall(matrix, mid, n) >= k {
			high = mid
		} else {
			low = mid + 1
		}
	}
	return low
}
func countKthSmall(matrix [][]int, mid int, n int) int {
	count := 0
	j := n - 1
	for i := 0; i < n; i++ {
		for j >= 0 && mid < matrix[i][j] {
			j--
		}
		count += j + 1
	}
	return count
}

func Test_378_kthSmallestElementinSortedMatrix() {
	kthSmallest_heap([][]int{[]int{1, 5, 9}, []int{10, 11, 13}, []int{12, 13, 15}}, 8)
}
