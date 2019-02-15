package leetcodeE

/*

# 674. Longest Continuous Increasing Subsequence

# Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

# Example 1:
# Input: [1,3,5,4,7]
# Output: 3
# Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3.
# Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4.

# Example 2:
# Input: [2,2,2,2,2]
# Output: 1
# Explanation: The longest continuous increasing subsequence is [2], its length is 1.
# Note: Length of the array will not exceed 10,000.
*/

import (
	"math"
)

func findLengthOfLCIS(nums []int) int {

	s, prev, maxv := -1, math.MaxInt32, 0

	for i, c := range nums {

		if i == 0 || c > prev {
			maxv = int(math.Max(float64(maxv), float64(i-s)))
		} else {
			s = i - 1
		}
		prev = c
	}

	return maxv
}
