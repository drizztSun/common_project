package leetcodem

/*
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
*/
import (
	"math/rand"
	"sort"
)

func partition(nums []int, i, j int) int {

	k, p := i, i
	for ; k <= j; k++ {

		if nums[k] > nums[i] {
			p++
			nums[k], nums[p] = nums[p], nums[k]
		}
	}

	nums[p], nums[i] = nums[i], nums[p]
	return p
}

func findKthLargest_1(nums []int, k int) int {

	i, j := 0, len(nums)-1
	for {
		idx := partition(nums, i, j)

		if idx == k-1 {
			return nums[idx]
		}

		if idx < k-1 {
			i = idx + 1
		} else {
			j = idx - 1
		}
	}
}

func findKthLargest_divide_and_conquer(nums []int, k int) int {

	quick_split := func(nums []int, s, e int) int {

		t, j := nums[s], s

		for i := s + 1; i <= e; i++ {
			if nums[i] > t {
				j++
				nums[i], nums[j] = nums[j], nums[i]
			}
		}
		nums[s], nums[j] = nums[j], nums[s]
		return j
	}

	s, e := 0, len(nums)-1
	for {

		m := quick_split(nums, s, e)

		if m-s+1 == k {
			return nums[m]
		} else if m-s+1 < k {
			k -= m - s + 1
			s = m + 1
		} else {
			e = m - 1
		}
	}
}

func swap(nums []int, i int, j int) {
	tmp := nums[i]
	nums[i] = nums[j]
	nums[j] = tmp
}

func partition_rand(nums []int) int {
	if len(nums) <= 1 {
		return 0
	}
	// Select a random element.
	idx := rand.Intn(len(nums))
	swap(nums, idx, len(nums)-1)
	pivot := nums[len(nums)-1]
	var i = 0
	// Loop invariants:
	// nums[0..i] <= pivot
	// nums[i..j+1] > pivot
	// nums[len(nums)-1] = pivot
	for j := 0; j < len(nums)-1; j++ {
		if nums[j] <= pivot {
			swap(nums, i, j)
			i++
		}
	}
	// Termination:
	// nums[i] > pivot
	swap(nums, i, len(nums)-1)
	return i
}

func findKthLargest_2(nums []int, k int) int {
	pivot := partition_rand(nums)
	// all entries in nums[0..pivot] <= nums[pivot], pivot elements
	// all entries in nums[pivot+1..] > nums[pivot], len(nums) -pivot-1 elements
	if k == len(nums)-pivot {
		return nums[pivot]
	} else if k < len(nums)-pivot {
		return findKthLargest(nums[pivot+1:], k)
	} else {
		return findKthLargest(nums[:pivot], k-len(nums)+pivot)
	}
}

func findKthLargest_sort(nums []int, k int) int {
	sort.Ints(nums)

	return nums[len(nums)-k]
}
