package leetcodeH

/*
713. Subarray Product Less Than K
*/

func numSubarrayProductLessThanK(nums []int, k int) int {

	cnt := 0
	left, right := 0, 0
	prod := 1

	for i, n := range nums {

		prod *= n
		right = i

		for prod >= k && left <= right {
			prod /= nums[left]
			left++
		}

		cnt += right - left + 1
	}

	return cnt
}
