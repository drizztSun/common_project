package leetcodeE

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

func findKthLargest(nums []int, k int) int {

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
