package leetcodeH

/*
786. K-th Smallest Prime Fraction

A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.

What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.

Examples:
Input: A = [1, 2, 3, 5], K = 3
Output: [2, 5]
Explanation:
The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
The third fraction is 2/5.

Input: A = [1, 7], K = 1
Output: [1, 7]
Note:

A will have length between 2 and 2000.
Each A[i] will be between 1 and 30000.
K will be between 1 and A.length * (A.length - 1) / 2.
*/

import (
	"container/heap"
)

type node struct {
	ratio float32
	i, j  int
}

type HeapNode []node

func (c HeapNode) Len() int {
	return len(c)
}

func (c HeapNode) Less(i, j int) bool {
	return c[i].ratio < c[j].ratio
}

func (c HeapNode) Swap(i, j int) {
	c[i], c[j] = c[j], c[i]
}

func (c *HeapNode) Pop() interface{} {
	old := *c
	n := len(old)
	x := old[n-1]
	*c = old[:n-1]
	return x
}

func (c *HeapNode) Push(x interface{}) {
	*c = append(*c, x.(node))
}

func KthSmallestPrimeFraction_heap(A []int, K int) []int {

	buf := &HeapNode{}
	N := len(A)

	for i := 0; i < N-1; i++ {
		heap.Push(buf, node{ratio: float32(A[i]) / float32(A[N-1]), i: i, j: N - 1})
	}

	res := []int{-1, -1}

	for ; K > 0 && len(*buf) > 0; K-- {

		n := heap.Pop(buf).(node)
		res[0], res[1] = A[n.i], A[n.j]

		if n.i != n.j-1 {
			heap.Push(buf, node{ratio: float32(A[n.i]) / float32(A[n.j-1]), i: n.i, j: n.j - 1})
		}
	}

	return res
}

func kthSmallestPrimeFraction_binary_search(A []int, K int) []int {

	left, right := 0.0, 1.0
	p, q := 0, 1

	n := len(A)
	for {
		p = 0
		count := 0

		mid := (left + right) / 2

		for i, j := 0, n-1; i < n; i++ {
			for j >= 0 && float64(A[i]) > mid*float64(A[n-1-j]) {
				j--
			}
			count += j + 1
			if j >= 0 && p*A[n-1-j] < q*A[i] {
				p, q = A[i], A[n-1-j]
			}
		}

		if count < K {
			left = mid
		} else if count > K {
			right = mid
		} else {
			return []int{p, q}
		}
	}
}

func kthSmallestPrimeFraction_binary_search_1(A []int, K int) []int {
	l, r := 0.0, 1.0
	n := len(A)
	p, q := 0, 1

	for {
		p = 0
		mid := l + (r-l)/2
		count := 0

		for i, j := 0, 0; i < n; i++ {
			for j < n && float64(A[i]) > mid*float64(A[j]) {
				j++
			}
			count += n - j
			if j < n && q*A[i] > A[j]*p {
				p, q = A[i], A[j]
			}
		}

		if count == K {
			return []int{p, q}
		} else if count > K {
			r = mid
		} else {
			l = mid
		}
	}
}

func Test_786_KthSmallestPrimFraction() {
	kthSmallestPrimeFraction_binary_search_1([]int{1, 2, 3, 5}, 3)
}
