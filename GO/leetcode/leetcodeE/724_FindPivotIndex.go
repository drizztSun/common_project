package leetcodeE

/*
724. Find Pivot Index

Given an array of integers nums, write a method that returns the "pivot" index of this array.

We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.

If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.

Example 1:

Input:
nums = [1, 7, 3, 6, 5, 6]
Output: 3
Explanation:
The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the sum of numbers to the right of index 3.
Also, 3 is the first index where this occurs.


Example 2:

Input:
nums = [1, 2, 3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.
*/

func pivotIndex(nums []int) int {
	sum := 0
	for _, c := range nums {
		sum += c
	}

	for i, left := 0, 0; i < len(nums); i++ {
		if left == sum-left-nums[i] {
			return i
		}
		left += nums[i]
	}

	return -1
}

func pivotIndex1(nums []int) int {

	left := make([]int, len(nums))
	right := make([]int, len(nums))

	for i := 1; i < len(nums); i++ {
		left[i] += left[i-1] + nums[i-1]
	}

	for i := len(nums) - 2; i >= 0; i-- {
		right[i] += right[i+1] + nums[i+1]
	}

	for i := 0; i < len(nums); i++ {
		if left[i] == right[i] {
			return i
		}
	}

	return -1
}
