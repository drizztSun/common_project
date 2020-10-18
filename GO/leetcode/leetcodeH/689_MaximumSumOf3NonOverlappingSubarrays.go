package leetcodeH

/*
689. Maximum Sum of 3 Non-Overlapping Subarrays

# In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

# Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

# Return the result as a list of indices representing the starting position of each interval (0-indexed).
# If there are multiple answers, return the lexicographically smallest one.

# Example:
# Input: [1,2,1,2,6,7,5,1], 2
# Output: [0, 3, 5]

# Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
# We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

# Note:
# nums.length will be between 1 and 20000.
# nums[i] will be between 1 and 65535.
# k will be between 1 and floor(nums.length / 3).
*/

func maxSumOfThreeSubarrays_dp(nums []int, k int) []int {

	W := make([]int, 0)
	cursum := 0
	for i, c := range nums {
		cursum += c
		if i >= k {
			cursum -= nums[i-k]
		}
		if i >= k-1 {
			W = append(W, cursum)
		}
	}

	left := make([]int, len(W))
	bestIndex := 0
	for i := range W {
		if W[i] > W[bestIndex] {
			bestIndex = i
		}
		left[i] = bestIndex
	}

	right := make([]int, len(W))
	bestIndex = len(W) - 1
	for j := len(W) - 1; j >= 0; j-- {
		if W[bestIndex] <= W[j] {
			bestIndex = j
		}
		right[j] = bestIndex
	}

	ans := []int{left[0], k, right[2*k]}
	for j := k; j < len(W)-k; j++ {
		i, z := left[j-k], right[j+k]
		if W[ans[0]]+W[ans[1]]+W[ans[2]] < W[i]+W[j]+W[z] {
			ans = []int{i, j, z}
		}
	}

	return ans
}
