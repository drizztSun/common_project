package leetcodeE

/*
53. Maximum Subarray

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.



Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Example 2:

Input: nums = [1]
Output: 1
Example 3:

Input: nums = [0]
Output: 0
Example 4:

Input: nums = [-1]
Output: -1
Example 5:

Input: nums = [-2147483647]
Output: -2147483647


Constraints:

1 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1


*/
import (
	"math"
)

func maxSubArray_dp(nums []int) int {

	res, total := nums[0], 0

	for _, c := range nums {

		total += c
		if total < c {
			total = c
		}

		if res < total {
			res = total
		}
	}

	return res
}

func search_divide_and_conquer(nums []int, s, e int) int {

	if s > e {
		return math.MinInt32
	}

	if s == e {
		return nums[s]
	}

	m := (s + e) / 2

	l, r := search_divide_and_conquer(nums, s, m), search_divide_and_conquer(nums, m+1, e)

	if l > r {
		r = l
	}

	lm, tlm := math.MinInt32, 0
	for i := m; i >= s; i-- {
		tlm += nums[i]
		if tlm > lm {
			lm = tlm
		}
	}

	rm, trm := math.MinInt32, 0
	for i := m + 1; i <= e; i++ {
		trm += nums[i]
		if trm > rm {
			rm = trm
		}
	}

	if r < lm+rm {
		r = lm + rm
	}

	return r
}

func maxSubArray_divide_and_conquer(nums []int) int {

	return search_divide_and_conquer(nums, 0, len(nums)-1)
}
