package leetcodeE

/*
215. Kth Largest Element in an Array


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
