package leetcodeH

import "container/heap"

/*
668. Kth Smallest Number in Multiplication Table

Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

Example 1:
Input: m = 3, n = 3, k = 5
Output:
Explanation:
The Multiplication Table:
1	2	3
2	4	6
3	6	9

The 5-th smallest number is 3 (1, 2, 2, 3, 3).
Example 2:
Input: m = 2, n = 3, k = 6
Output:
Explanation:
The Multiplication Table:
1	2	3
2	4	6

The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
Note:
The m and n will be in the range [1, 30000].
The k will be in the range [1, m * n]

*/

type point struct {
	Multi int
	i, j  int
}

type points []*point

func (obj points) Len() int {
	return len(obj)
}

func (obj points) Less(i, j int) bool {
	return obj[i].Multi < obj[j].Multi
}

func (obj points) Swap(i, j int) {
	obj[i], obj[j] = obj[j], obj[i]
}

func (obj *points) Push(x interface{}) {
	item := x.(point)
	*obj = append(*obj, &item)
}

func (obj *points) Pop() interface{} {
	old := *obj
	n := len(old)
	x := old[n-1]
	*obj = old[:n-1]
	return x
}

func findKthNumber(m int, n int, k int) int {

	obj := points{}
	for i := 0; i < m; i++ {
		obj = append(obj, &point{Multi: (i + 1), i: i, j: 0})
	}
	heap.Init(&obj)

	var item point
	for k > 0 {
		item := heap.Pop(&obj).(*point)
		if item.j < n {

			heap.Push(&obj, &point{Multi: (item.i + 1) * (item.j + 2), i: item.i, j: item.j + 1})
		}

		k--
	}

	return item.Multi
}
