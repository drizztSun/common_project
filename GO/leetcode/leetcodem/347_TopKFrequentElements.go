package leetcodem

/*
347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
You can return the answer in any order.
*/
import (
	"container/heap"
)

type heapVtoK [][2]int

func (this heapVtoK) Len() int {
	return len(this)
}

func (this heapVtoK) Less(i, j int) bool {
	return this[i][0] > this[j][0] || (this[i][0] == this[j][0] && this[i][1] < this[j][1])
}

func (this heapVtoK) Swap(i, j int) {
	this[i], this[j] = this[j], this[i]
}

func (this *heapVtoK) Push(x interface{}) {
	*this = append(*this, x.([2]int))
}

func (this *heapVtoK) Pop() interface{} {
	old := *this
	n := len(old)

	x := old[n-1]
	*this = old[:n-1]
	return x
}

func topKFrequent(nums []int, k int) []int {

	cnt := make(map[int]int)
	for i := range nums {
		cnt[nums[i]]++
	}

	buf := make(heapVtoK, 0)

	for k := range cnt {
		buf = append(buf, [2]int{cnt[k], k})
	}

	heap.Init(&buf)
	res := []int{}
	for ; k > 0; k-- {
		key := heap.Pop(&buf).([2]int)
		res = append(res, key[1])
	}
	return res
}
