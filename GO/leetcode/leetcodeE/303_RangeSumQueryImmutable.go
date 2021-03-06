package leetcodeE

/*
303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3


Constraints:

You may assume that the array does not change.
There are many calls to sumRange function.
0 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5
0 <= i <= j < nums.length
*/

type NumArray struct {
	NumSum []int
}

func Constructor(nums []int) NumArray {

	sumarr := make([]int, len(nums)+1)

	for i := range nums {
		sumarr[i+1] = sumarr[i] + nums[i]
	}

	return NumArray{
		NumSum: sumarr,
	}
}

func (this *NumArray) SumRange(i int, j int) int {

	if j < i || j >= len(this.NumSum) {
		return 0
	}

	return this.NumSum[j+1] - this.NumSum[i]
}
