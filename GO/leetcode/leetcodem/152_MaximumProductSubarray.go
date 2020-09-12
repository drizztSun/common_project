package leetcodem

/*
152. Maximum Product Subarray

Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

func maxProduct_dp(nums []int) int {

	maxV, minV := 1, 1
	res := nums[0]

	for _, c := range nums {

		if c < 0 {
			maxV, minV = minV, maxV
		}

		if maxV*c < c {
			maxV = c
		} else {
			maxV = maxV * c
		}

		if minV*c > c {
			minV = c
		} else {
			minV = minV * c
		}

		if res < maxV {
			res = maxV
		}
	}

	return res
}

func maxProduct_(nums []int) int {
    front, maxProduct := 0, nums[0]
	for front < len(nums) {
		if nums[front] == 0 {
			if maxProduct < 0 {
				maxProduct = 0
			}
			front++
			continue
		}

		end := front
		currProduct := 1
		for ; front < len(nums) && nums[front] != 0; front++ {
			if currProduct *= nums[front]; currProduct > maxProduct {
				maxProduct = currProduct
			}
		}

		for ; currProduct < 0 && end < front-1; end++ {
			if currProduct /= nums[end]; currProduct > maxProduct {
				maxProduct = currProduct
			}
		}
	}

	return maxProduct
}